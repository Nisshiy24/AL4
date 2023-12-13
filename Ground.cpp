#include "Ground.h"
#include <cassert>
//#include "ImGuiManager.h"
//#include "Vector3.h"


void Ground::Initialize(Model* model) {
	assert(model);

	//textureHandleGround_ = textureHandle;
	model_ = model;

	worldTransform_.Initialize();
}

void Ground::Update() {}

void Ground::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection);
}
