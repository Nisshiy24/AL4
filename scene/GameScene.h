#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include <memory>
#include "Ground.h"
#include "Skydome.h"
#include "DebugCamera.h"
#include "FllowCamera.h"
#include "BaseCharacter.h"
#include "Enemy.h"
#include "DebugText.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Title();
	void Rulu();
	void GamePlay();
	void GameClear();
	void GameStar();

	uint32_t textureHandleBlack_ = 0;
	Sprite* spriteBlack_ = nullptr;

		uint32_t texturehandleTitleEnter_ = 0;
	Sprite* spriteTitleEnter_ = nullptr;

	uint32_t texturehandlebackground_ = 0;
	Sprite* spritebackground_ = nullptr;

	uint32_t texturehandletitle_ = 0;
	Sprite* spritebacktitle_ = nullptr;

	uint32_t texturehandlerulu_ = 0;
	Sprite* spriterulu_ = nullptr;

	uint32_t texturehandlescore_ = 0;
	Sprite* spritescore_ = nullptr;




	uint32_t texturehandlescore0_ = 0;
	Sprite* spritescore0_ = nullptr;

	uint32_t texturehandlescore100_ = 0;
	Sprite* spritescore100_ = nullptr;

	uint32_t texturehandlescore200_ = 0;
	Sprite* spritescore200_ = nullptr;

	uint32_t texturehandlescore300_ = 0;
	Sprite* spritescore300_ = nullptr;

	uint32_t texturehandlescore400_ = 0;
	Sprite* spritescore400_ = nullptr;

	uint32_t texturehandlescore500_ = 0;
	Sprite* spritescore500_ = nullptr;

	uint32_t texturehandlescore600_ = 0;
	Sprite* spritescore600_ = nullptr;

	uint32_t texturehandlescore700_ = 0;
	Sprite* spritescore700_ = nullptr;

	uint32_t texturehandlescore800_ = 0;
	Sprite* spritescore800_ = nullptr;

	uint32_t texturehandlescore900_ = 0;
	Sprite* spritescore900_ = nullptr;

	uint32_t texturehandlescore1000_ = 0;
	Sprite* spritescore1000_ = nullptr;

	uint32_t texturehandlescore1100_ = 0;
	Sprite* spritescore1100_ = nullptr;

	uint32_t texturehandlescore1200_ = 0;
	Sprite* spritescore1200_ = nullptr;

	uint32_t texturehandlescore1300_ = 0;
	Sprite* spritescore1300_ = nullptr;

	uint32_t texturehandlescore1400_ = 0;
	Sprite* spritescore1400_ = nullptr;

	uint32_t texturehandlescore1500_ = 0;
	Sprite* spritescore1500_ = nullptr;


	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	int gametimer = 2000;
	int score = 0;
	int scenmode = 0;
	int titletimer = 0;
	bool flag_ = false;
	float black = 1.0f;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	DebugText* debugText_ = nullptr;



	/// <summary>
	/// ゲームシーン用
	/// </summary>
	/// 
	// 自キャラ
	// Player* player_ = nullptr;
	ViewProjection viewProjection_;
	uint32_t textureHandle_ = 0u;
	// uint32_t textureHandleGround_ = 0u;
	// std::unique_ptr<Model> model_;

	std::unique_ptr<Model> modelFighter_;
	std::unique_ptr<Model> modelGround_;
	std::unique_ptr<Model> modelSkydome_;

	//3Dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterHead_;
	std::unique_ptr<Model> modelFighterL_arm_;
	std::unique_ptr<Model> modelFighterR_arm_;


	// 3Dモデル
	std::unique_ptr<Model> modelEnemyBody_;
	std::unique_ptr<Model> modelEnemyL_arm_;
	std::unique_ptr<Model> modelEnemyR_arm_;






	std::unique_ptr<Player> player_;
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Enemy> enemy_;

	//デバックカメラ
	std::unique_ptr<DebugCamera> debugCamera_;
	//デバックカメラ有効
	bool isDebugCameraActive_ = false;

	//追従カメラ
	std::unique_ptr<FollowCamera> fllowCamera_;
};
