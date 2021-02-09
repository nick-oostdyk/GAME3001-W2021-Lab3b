#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene() {
	PlayScene::start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::draw() {
	drawDisplayList();

	if (EventManager::Instance().isIMGUIActive()) {
		GUI_Function();
	}

	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
}

void PlayScene::update() {
	updateDisplayList();
}

void PlayScene::clean() {
	removeAllChildren();
}

void PlayScene::handleEvents() {
	EventManager::Instance().update();

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE)) {
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1)) {
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2)) {
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void PlayScene::start() {
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_buildGrid();

	m_pTarget = new Target();
	m_pTarget->getTransform()->position = GetTile(15, 11)->getTransform()->position + offset;
	m_pTarget->SetGridPos(15, 11);
	addChild(m_pTarget);

	ComputeTileCosts();

}

void PlayScene::m_buildGrid() {
	auto tileSize = Config::TILE_SIZE;

	for (int row = 0; row < Config::ROW_NUM; ++row) {

		for (int col = 0; col < Config::COL_NUM; ++col) {

			Tile *tile = new Tile(); // create empty tile
			tile->getTransform()->position = glm::vec2(col * tileSize, row * tileSize);
			tile->SetGridPos(col, row);
			addChild(tile);
			tile->AddLabels();
			tile->setEnabled(false);
			m_pGrid.push_back(tile);
		}
	}

	for (int row = 0; row < Config::ROW_NUM; ++row) {

		for (int col = 0; col < Config::COL_NUM; ++col) {

			Tile *tile = GetTile(col, row);

			if (row == 0) {
				tile->SetNeighbourTile(TOP_TILE, nullptr);
			} else {
				tile->SetNeighbourTile(TOP_TILE, GetTile(col, row - 1));
			}

			if (col == Config::COL_NUM - 1) {
				tile->SetNeighbourTile(RIGHT_TILE, nullptr);
			} else {
				tile->SetNeighbourTile(RIGHT_TILE, GetTile(col + 1, row));
			}

			if (row == Config::ROW_NUM - 1) {
				tile->SetNeighbourTile(BOTTOM_TILE, nullptr);
			} else {
				tile->SetNeighbourTile(BOTTOM_TILE, GetTile(col, row + 1));
			}

			if (col == 0) {
				tile->SetNeighbourTile(LEFT_TILE, nullptr);
			} else {
				tile->SetNeighbourTile(LEFT_TILE, GetTile(col - 1, row));
			}
		}
	}
}

void PlayScene::ComputeTileCosts() {

	for (auto tile : m_pGrid) {

		auto distance = Util::distance(m_pTarget->GetGridPos(), tile->GetGridPos());
		tile->SetTileCost(distance);
	}
}

void PlayScene::m_setGridEnabled(bool state) {
	for (auto tile : m_pGrid) {
		tile->setEnabled(state);
		tile->SetLabelsEnabled(state);
	}

	if (state == false) {
		SDL_RenderClear(Renderer::Instance()->getRenderer());
	}
}

Tile *PlayScene::GetTile(const int _col, const int _row) {
	return m_pGrid[_row * Config::COL_NUM + _col];
}

void PlayScene::GUI_Function() {
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("GAME3001 - Lab 3", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove);

	static bool isGridEnabled = false;
	if (ImGui::Checkbox("Grid Enabled", &isGridEnabled)) {
		// toggle grid on/off
		m_setGridEnabled(isGridEnabled);
	}

	ImGui::Separator();

	static int targetPosition[] = { m_pTarget->GetGridPos().x, m_pTarget->GetGridPos().y };
	if (ImGui::SliderInt2("Target Position", targetPosition, 0, Config::COL_NUM - 1)) {

		if (targetPosition[1] > Config::ROW_NUM - 1)
			targetPosition[1] = Config::ROW_NUM - 1;

		SDL_RenderClear(Renderer::Instance()->getRenderer());
		m_pTarget->SetGridPos(targetPosition[0], targetPosition[1]);
		m_pTarget->getTransform()->position = GetTile(targetPosition[0], targetPosition[1])->getTransform()->position + offset;
		ComputeTileCosts();
		SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);
		SDL_RenderPresent(Renderer::Instance()->getRenderer());
	}

	if (ImGui::Button("Start")) {

	}

	ImGui::SameLine();

	if (ImGui::Button("Reset")) {

	}

	ImGui::Separator();


	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}