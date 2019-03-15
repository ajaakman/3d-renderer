emcc -std=c++11 "Engine/Graphics/GUtility/VertexLayout.cpp" "Engine/Graphics/Meshes/Mesh.cpp" "Engine/Graphics/Cameras/Camera2D.cpp" "Engine/Graphics/Cameras/Camera3D.cpp" "Engine/Graphics/GUtility/TextureCache.cpp" "Engine/Graphics/Renderables/Renderable.cpp" "Engine/Graphics/Materials/Material.cpp" "Engine/Graphics/Renderer.cpp" "Engine/Graphics/GLBase/Texture.cpp" "Engine/Graphics/GLBase/Program.cpp" "Engine/Graphics/GLBase/ElementArrayBuffer.cpp" "Engine/Graphics/GLBase/Buffer.cpp" "Engine/IO/Window.cpp" "Engine/Utility/Error.cpp" "Engine/Libraries/stbi/stbi.cpp" "Engine/Engine.cpp" "Test/game.cpp" "Test/main.cpp" -s USE_GLFW=3 -s FULL_ES3=1 -DEMSCRIPTEN=1 --memory-init-file 0 --embed-file Resources -O3 -o Web\WebGl.html