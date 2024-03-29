#include "pxr/imaging/glf/glew.h"
#include "pxr/imaging/glf/contextCaps.h"

#include "pxr/imaging/hd/renderIndex.h"
#include "pxr/imaging/hd/engine.h"
#include "pxr/imaging/hd/task.h"
#include "pxr/imaging/hd/renderPassState.h"
#include "pxr/imaging/hdx/renderTask.h"

#include "pxr/imaging/hdSt/renderDelegate.h"
#include "pxr/imaging/hdSt/renderPass.h"

#include "pxr/imaging/garch/glDebugWindow.h"

#include "pxr/usd/sdf/path.h"

#include "SceneDelegate.h"

#include <iostream>


class DebugWindow : public pxr::GarchGLDebugWindow {
public:
	DebugWindow(const char *title, int width, int height) : GarchGLDebugWindow(title, width, height) {
		// create a RenderDelegate which is required for the RenderIndex
		renderDelegate.reset( new pxr::HdStRenderDelegate() );

		// RenderIndex which stores a flat list of the scene to render
		index = pxr::HdRenderIndex::New( renderDelegate.get() );

		// names for elements in the RenderIndex
		pxr::SdfPath renderSetupId("/renderSetup");
		pxr::SdfPath renderId("/render");
		pxr::SdfPath sceneId("/");

		// SceneDelegate can query information from the client SceneGraph to update the renderer
		sceneDelegate = new SceneDelegate( index, sceneId );

		// Create two tasks (render setup & render) to the RenderIndex
		sceneDelegate->AddRenderSetupTask(renderSetupId);
		sceneDelegate->AddRenderTask(renderId);
		
		// I can move these into return values for SceneDelegate::AddRenderSetupTask && AddRenderTask functions 
		pxr::HdTaskSharedPtr renderSetupTask = index->GetTask(renderSetupId);
		pxr::HdTaskSharedPtr renderTask      = index->GetTask(renderId);
	
		tasks = {renderSetupTask, renderTask};
	}

	void OnPaintGL() override {
		if (!mGlInitialized) {
			[[maybe_unused]] bool glewInit = pxr::GlfGlewInit();
			assert(glewInit);

			pxr::GlfContextCaps::InitInstance(); // call on gl thread
			std::cout << "glVersion: " << pxr::GlfContextCaps::GetInstance().glVersion << std::endl;
			std::cout << "glslVersion: " << pxr::GlfContextCaps::GetInstance().glslVersion << std::endl;
			mGlInitialized = true;
		}

		pxr::GarchGLDebugWindow::OnPaintGL();

		// clear to blue
		glClearColor(0.1f, 0.1f, 0.3f, 1.0 );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glDepthFunc(GL_LESS);
		glEnable(GL_DEPTH_TEST);

		// execute the render tasks
		engine.Execute( index, &tasks );
	}

private:
	SceneDelegate *sceneDelegate;
	pxr::HdTaskSharedPtrVector tasks;
	pxr::HdEngine engine;
	pxr::HdRenderIndex *index;
	boost::shared_ptr<pxr::HdStRenderDelegate> renderDelegate;

	bool mGlInitialized = false;
};


int main(int argc, char** argv) {
	DebugWindow window("hydra - Hello World", 1280, 720);
	window.Init();

	window.Run();

	return 0;
}