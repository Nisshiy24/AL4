#include "Enemy.h"
#include "MathUtilityForText.h"
#include "time.h"

void Enemy::Initialize(const std::vector<Model*>& models) { 
	
	BaseCharacter::Initialize(models);
	




		

			worldTransformBody_.Initialize();
			worldTransformBody_.parent_ = &worldTransform_;

			worldTransformL_arm_.Initialize();
			worldTransformL_arm_.parent_ = &worldTransformBody_;
			worldTransformL_arm_.translation_.x = -0.27337f;
			worldTransformL_arm_.translation_.y = 0.01077f;

			worldTransformR_arm_.Initialize();
			worldTransformR_arm_.parent_ = &worldTransformBody_;
			worldTransformR_arm_.translation_.x = +0.27337f;
			worldTransformR_arm_.translation_.y = 0.01077f;

		

			



		
	
		srand((unsigned int)time(NULL));
}


void Enemy::Update() {
	UpdateGimmick();

	//移動の速さ
	const float speed = 0.1f;

	worldTransform_.rotation_.y += 0.01f;

	//移動量
	Vector3 move = {0.0f, 0.0f, speed};

	//回転行列
	Matrix4x4 matRotY = MakeRotateYMatrix(worldTransform_.rotation_.y);

	//移動量を回転に合わせて回転させる
	move = TransformNormal(move, matRotY);

	worldTransform_.translation_ += move;

	//移動
	worldTransform_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();



	
}


void Enemy::Draw(const ViewProjection& viewProjection)
{
	if (aliveFlag_ == 1) {
		// 3Dモデルを描画
		models_[kModelIndexBody]->Draw(worldTransformBody_, viewProjection);
		models_[kModelIndexL_arm]->Draw(worldTransformL_arm_, viewProjection);
		models_[kModelIndexR_arm]->Draw(worldTransformR_arm_, viewProjection);
	}
}

void Enemy::UpdateGimmick()
{
	
	const float idleArmAngleMax = 30.0f;
	worldTransformL_arm_.rotation_.x = std::sin(floatingPrameter) * idleArmAngleMax / 180.0f * PI;
	worldTransformR_arm_.rotation_.x = std::sin(floatingPrameter) * idleArmAngleMax / 180.0f * PI;


	 if (rand() % 10 == 0) {
		if (aliveFlag_ == 0) {
			int x = rand() % 80;
			float x2 = (float)x / 10 - 4;
			worldTransform_.translation_.x = x2;
			aliveFlag_ = 1;
		}
	}


}

void Enemy::Hit()
{

	 aliveFlag_ = 0; 

	

}