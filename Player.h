#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <Input.h>

class Player {

	public:
		//初期化
	    void Initialize(Model* model);

		//更新
	    void Update();

		//描画
	    void Draw(const ViewProjection& viewProjection);

		const WorldTransform& GetWorldTransform() { return worldTransform_; }

		void SetViewProjection(const ViewProjection* viewProjection) {
		    viewProjection = viewProjection;
		}


		private:
			//ワールド変換データ
	        WorldTransform worldTransform_;

			//モデル
	        Model* model_ = nullptr;

			//テクスチャハンドル
	        uint32_t textureHandle_ = 0u;

			//入力
	        Input* input_ = nullptr;

			//カメラのビュープロジェクション
	        const ViewProjection* viewProjection_ = nullptr;
		


};
