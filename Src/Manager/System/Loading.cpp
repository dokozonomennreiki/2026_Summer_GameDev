#include "Loading.h"
#include <DxLib.h>
#include <iostream>
#include "../../Application.h"
#include "../Generic/ResourceManager.h"

Loading* Loading::instance_ = nullptr;

void Loading::CreateInstance(void)
{
	if (!instance_)
	{
		instance_ = new Loading();
	}
}

Loading* Loading::GetInstance(void)
{
	return instance_;
}

void Loading::DestroyInstance(void)
{
	if (instance_)
	{
		delete instance_;
		instance_ = nullptr;
	}
}

Loading::Loading(void)
	: isLoading_(false)
	, progress_(0.0f)
	, imageHandle_(-1)
{
}

Loading::~Loading(void)
{
}

void Loading::Initialize(void)
{
	isLoading_ = false;
	progress_ = 0.0f;
}

void Loading::StartAsyncLoad(std::function<void()> loadFunc)
{
	if (isLoading_)
	{
		return;
	}

	Initialize();
	isLoading_ = true;

	if (loadFunc)
	{
		loadFunc();
	}
}

void Loading::Update(void)
{
	if (!isLoading_)
	{
		return;
	}

	const int LOAD_COUNT = GetASyncLoadNum();

	if (progress_ < 100.0f)
	{
		progress_ += 0.05f;
	}

	if (progress_ >= 100.0f)
	{
		if (LOAD_COUNT == 0)
		{
			EndAsyncLoad();
		}
		else
		{
			progress_ = 99.9f;
		}
	}
}

void Loading::Draw(void)
{
	const int screenWidth = Application::SCREEN_SIZE_X;
	const int screenHeight = Application::SCREEN_SIZE_Y;

	ClearDrawScreen();

	DrawBox(0, 0, screenWidth, screenHeight, GetColor(0, 0, 0), TRUE);

	const int movementRangeWidth = 800;
	const int centerX = screenWidth / 2;
	const int centerY = screenHeight / 2;

	const float currentProgress = progress_;

	// 画像のサイズを取得
	int imageWidth = 0;
	int imageHeight = 0;
	GetGraphSize(imageHandle_, &imageWidth, &imageHeight);

	// 画像が画面中央を基準に左右へ綺麗に移動するための開始地点と終了地点を計算
	const int startX = centerX - movementRangeWidth / 2 - imageWidth / 2;
	const int endX = centerX + movementRangeWidth / 2 - imageWidth / 2;

	// 現在の進捗率を基に、開始地点から終了地点までのX座標を線形補間
	const int imageX = static_cast<int>(startX + (endX - startX) * (currentProgress / 100.0f));
	const int imageY = centerY - imageHeight / 2;

	DrawRotaGraph(imageX, imageY, 0.5f, 0.0f, imageHandle_, true);
}

void Loading::EndAsyncLoad(void)
{
	isLoading_ = false;
	progress_ = 100.0f;
}

bool Loading::IsLoading(void) const
{
	return isLoading_;
}

int Loading::GetProgress(void) const
{
	return static_cast<int>(progress_);
}

void Loading::SetProgress(float progress)
{
	if (progress < 0.0f)
	{
		progress = 0.0f;
	}
	if (progress > 100.0f)
	{
		progress = 100.0f;
	}
	progress_ = progress;
}