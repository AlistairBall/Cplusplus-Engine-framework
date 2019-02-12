#include "OctSpacialPartition.h"

int OctNode::childNum = 0;




OctNode::OctNode(glm::vec3 position_, float size_, OctNode * parent_)
{
	octBounds = new BoundingBox();
	octBounds->minVert = position_;
	octBounds->maxVert = position_ + glm::vec3(size_);

	size = size_;

	for (int i = 0; i < 8; i++) {
		children[i] = 0;
	}
	parent = parent_;
}

OctNode::~OctNode()
{
	delete octBounds;
	octBounds = nullptr;

	if (objectList.size() > 0) {
		for (auto go : objectList) {
			go = nullptr;
		}
		objectList.clear();
		objectList.shrink_to_fit();
	}

	for (int i = 0; i < 8; i++) {
		if (children[i] != nullptr) {
			delete children[i];
			children[i] = nullptr;
		}
	}
}

void OctNode::Octify(int depth)
{
	if (depth > 0 && this) {
		float half = size / 2.0f;
		children[OCT_TLF] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_BLF] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[OCT_BRF] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z + half), half, this);
		children[OCT_TRF] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z + half), half, this);
		children[OCT_TLR] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y + half, octBounds->minVert.z), half, this);
		children[OCT_BLR] = new OctNode(glm::vec3(octBounds->minVert.x, octBounds->minVert.y, octBounds->minVert.z), half, this);
		children[OCT_BRR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y, octBounds->minVert.z), half, this);
		children[OCT_TRR] = new OctNode(glm::vec3(octBounds->minVert.x + half, octBounds->minVert.y + half, octBounds->minVert.z), half, this);
		// fill in the rear section

		childNum += 8;

	} 
	if (depth > 0 && this) {
		for (int i = 0; i < 8; i++) {
			children[i]->Octify(depth - 1);
			
		}
	}
}

OctNode * OctNode::GetParent()
{
	return parent;
}

OctNode * OctNode::GetChild(OctChildren type_)
{
	return children[type_];
}

void OctNode::AddCollisionObject(GameObject * obj_)
{
	objectList.push_back(obj_);
	std::cout << "Added " << obj_->GetTag() << " to cell: " << glm::to_string(octBounds->maxVert) << std::endl;
}

int OctNode::GetObjectCount() const
{
	return objectList.size();
}

bool OctNode::IsLeaf() const
{
	if (children[0] == 0 || children[0] == nullptr) {
		return true;
	}
	return false;
}

BoundingBox * OctNode::GetBoundingBox() const
{
	return octBounds;
}

int OctNode::GetChildCount() const
{
	return childNum;
}



OctSpacialPartition::OctSpacialPartition(float worldSize_)
{
	root = new OctNode(glm::vec3(-(worldSize_ / 2.0f)), worldSize_, 0);
	root->Octify(3);
	std::cout << "There are " << root->GetChildCount() << " child nodes" << std::endl;
}


OctSpacialPartition::~OctSpacialPartition()
{
	delete root;
	root = nullptr;

	if (rayIintersectionList.size() > 0) {
		for (auto cell : rayIintersectionList) {
			cell = nullptr;
		}
		rayIintersectionList.clear();
		rayIintersectionList.shrink_to_fit();
	}
}

void OctSpacialPartition::AddObject(GameObject * obj_)
{
	AddObjectTocell(root, obj_);
}

GameObject * OctSpacialPartition::GetCollision(Ray ray_)
{
	rayIintersectionList.clear();
	PrepareCollisionQuery(root, ray_);
	GameObject* result = nullptr;
	float shortestDistance = FLT_MAX;
	for (auto c : rayIintersectionList) {
		for (auto go : c->objectList) {
			if (ray_.isColliding(&go->GetBoundingBox())) {
				if (ray_.intersectionDistance < shortestDistance) {
					result = go;
					shortestDistance = ray_.intersectionDistance;
				}
			}
		}
		if (result != nullptr) {
			return result;
		}
	}
	return nullptr;
}

void OctSpacialPartition::AddObjectTocell(OctNode * cell_, GameObject * obj_)
{
	if (obj_->GetBoundingBox().Intersects(cell_->GetBoundingBox())) {
		if (cell_->IsLeaf())
			cell_->AddCollisionObject(obj_);
		else {
			for each (OctNode* c in cell_->children)
				AddObjectTocell(c, obj_);
		}
	}
}

void OctSpacialPartition::PrepareCollisionQuery(OctNode * cell_, Ray ray_)
{
	for each (OctNode* c in cell_->children)
	{
		if (!c->IsLeaf())
			PrepareCollisionQuery(c, ray_);

		else
			for each (GameObject* o in c->objectList)
				if (ray_.isColliding(&o->GetBoundingBox()))
					rayIintersectionList.push_back(c);
	}
}