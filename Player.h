#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>
#include "BaseCharacter.h"
#include "ViewProjection.h"

class Player : public BaseCharacter{

	public:

		enum {
			kModelIndexBody,
			kModelIndexHead,
			kModelIndexL_arm,
			kModelIndexR_arm
		};
		

		//初期化
	    void Initialize(const std::vector<Model*> & models) override;

		//更新
	    void Update()override;

		//描画
	    void Draw(const ViewProjection& viewProjection)override;

		const WorldTransform& GetWorldTransform() { return worldTransform_; }

		void SetViewProjection(const ViewProjection* viewProjection) {
		    viewProjection_ = viewProjection;
		}

		//浮遊ギミック
	    void InitializeFloatingGimmick();

		//浮遊ギミック更新
	    void UpdateFloatingGimmick();


		float GetX() { return worldTransform_.matWorld_.m[3][0]; }
	    float GetY() { return worldTransform_.matWorld_.m[3][1]; }
	    float GetZ() { return worldTransform_.matWorld_.m[3][2]; }

		private:
			//ワールド変換データ
	        WorldTransform worldTransform_;
	        WorldTransform worldTransformBody_;
	        WorldTransform worldTransformHead_;
	        WorldTransform worldTransformL_arm_;
	        WorldTransform worldTransformR_arm_;


			//モデル
	        //Model* model_ = nullptr;


			//3Dモデル
	        Model* modelFighterBody_;
	        Model* modelFighterHead_;
	        Model* modelFighterL_arm_;
	        Model* modelFighterR_arm_;

			

			//テクスチャハンドル
	        uint32_t textureHandle_ = 0u;

			//入力
	        Input* input_ = nullptr;

			//浮遊ギミックの媒介変数
	        float floatingParameter_ = 0.0f;

			//カメラのビュープロジェクション
	        const ViewProjection* viewProjection_ = nullptr;
		


};
