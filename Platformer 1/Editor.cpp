#include "Editor.h"
#include "globals.h"
#include "GameObjectManager.h"
#include "ImageManager.h"

Editor::Editor(void)
{
	selectedObject=WALL;
}


Editor::~Editor(void)
{
}


Editor& Editor::GI()
{
	static Editor instance;
	return instance;
}

void Editor::Update()
{
	
}

void Editor::Draw()
{

}

//private
void Editor::CreateObject()
{
	
}

void Editor::DeleteObject()
{

}

void Editor::NextObject()
{

}

void Editor::PreviousObject()
{

}

void Editor::SetSelectedObject(int object)
{

	objImage = ImageManager::GetInstance().GetImage(object);
}