//
// Created by Tiern on 19/02/2026.
//
#include "TempEditor/EditorStartup.h"

#include "Editor.h"
#include "TempEditor/SimpleMapEditor.h"

void EditorStartup::Execute()
{
    SimpleMapEditor* editor= (new GameObject("Editor"))->AddBehaviour<SimpleMapEditor>();
}
