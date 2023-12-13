#include "Player.h"
#include <cassert>
#include "ImGuiManager.h"
#include "Vector3.h"



void Player::Initialize(Model* model) {

assert(model);

//textureHandle_ = textureHandle;
model_ = model;

worldTransform_.Initialize();


}

void Player::Update() {  }

void Player::Draw(const ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


