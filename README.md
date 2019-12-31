# New OpenGL-Phyics-
By: Kacper Mazur

Repo-Link: (https://github.com/kacpermazur/OpenGL-Phyics-)

Video Link: (https://www.youtube.com/watch?v=7oLIzQMvT8w&feature=youtu.be)

## How does the user interact/open with your executable?
•	**Controls:**

* W – Move Up
* S – Move Down
* A – Move Left
* D – Move Right

* Move Into the other cube and once near enough the cubes will bunch away from each other to indicate a collision at correct direction (console will display from which side the collision happened)

* Open the exe file for a simple collision test between blocks (note there will be no console) Alternatively open up the sln file and press run to view the console output.
## How does the program code work?
The program is written in C++ using number of libraries, GLEW, GLFW, GLM and stb image. The program will first call the application class first, it will set its state, parse the delta time to the respective functions (more detail in the next section, just an abstract overview) and most of the initialization and updating will reside in that class. Another important Class is the Resource Manager that handles all the shader loading, textures and uniform binding to the respective shader. The renderer will draw the mesh onto the screen and update when ever any uniforms are set e.g. movement. Last notable Class is the GameObject class which allows the user to easily set textures to mesh, move, scale and rotate them as well as changing their colours. These game Object also have a draw function that takes in the respective renderer. (More information below about each class and any other supporting class)
 
## How do the classes and functions fit together and who does what?
**Application Class:**
*	Application (constructor)
	*	Initializes all the internal variables and the screen width/ hight
*	Application (Destructor)
	*	Deletes any heap allocated memory when the program is closed such as game objects.
*	Initialize
	*	Gets called when the program is started, it will Initialize anything inside that function (gets called once)
	*	Used mostly to load in all the resources and set-up all the variables such as the projection matrix, creating new game objects
*	InputHandler
	*	Any input such as GLFW key press gets processed in this function
	*	Currently it used to move the player game object position with delta time velocity (WASD input and framerate independent) 
*	Update
	*	Calls the physics update functions
	*	Planned to be used for anything that requires function call after every draw call
*	PhysicsUpdate
	*	Similar to update however moved out, used for any physics calls after update is finished
*	Render
	*	Called each frame as well after the physics called (init -> input -> update -> PhysicsUpdate -> Render), calls the draw functions of gameobjects.

**Extra Functions within the Application Class (Physics Part of it)**

*	OnEnterTrigger2D
	*	Returns true if both game objects intersect each other x, y
	*	Planned to be used on planes
*	OnEnterTrigger3D
	*	Cube mesh collider, checks if game objects intersect each other at x, y, z
*	ColDirection
	*	Returns a vector3 based on which side the collision came from relative to the “other” game object. 
	*	Checks respective side and sees if other collision float values are less it, if so, it will return a vector3.
	*	Used after OnEnterTrigger3D is true, expressive calculation.
	
**GameObject Class:**
*	Public variables for position, size, rot, color and rotation
*	GameObject (Constructor)
	*	Takes in the position size, texture rotation and color and parses them into the variables
	*	Or it creates an empty gameobject where user can set properties later through accessing the variables
*	Draw
	*	Takes a renderer reference and calls it draw function while parsing the correct respective variables
	
**Renderer Class:**
*	InitializeRenderData
	*	Creates a cube Mesh
	*	Binds the VBO and IBOs
	*	Uses VertexLayout class helper to set the attribPointers
*	Renderer (Constructor)
	*	Takes in the Shader
*	Renderer (Destructor)
	*	Deletes vertex arrays
*	Draw
	*	Binds the shader
	*	Sets the model position, rotation and scale (uniforms)
	*	Binds the texture
	*	Draws the elements
	
**ResourceManager Class:**
*	Shader -  Map (variable for caching)
*	Texture - Map (variable for caching)
*	LoadShader
	*	Calls LoadShaderFromFile
	*	Adds it to the map
	*	Returns it 	*(1)
*	GetShader
	*	Returns shader from map 	*(1) 
*	LoadTexture
	*	Calls LoadTextureFromFile
	*	Adds it to the map
	*	Returns it 	*(1)
*	GetTexture
	*	Returns shader from map 	*(1) 
*	Clear
	*	Deletes all shaders from the map and textures from its map
*	LoadShaderFromFile
	*	loads Shader from File path (frag and vs)
	*	compiles the vertex and fragment shader
	*	returns the new shader
*	LoadTextureFromFile
	*	Stbi call, loads the image data with width, hight, bits per pixels and char pointer of the actual image data
	*	Sets these variables into the texture generate function
	*	Returns the textures

**Shader Class:**
*	Bind
	*	Binds the current shader
*	Compile
	*	Calls CompieShaderID for vertex and fragment shader
	*	Attaches the shaders, links the program and deletes the shader source code once its loaded into openGL
*	SetUniformXX (XX = data types, all same in principle)
	*	Binds shader and sets a uniform in that shader
*	ShaderErrorCheck
	*	Gets the status to see if the shader program compiled
	*	Gets the shader info and couts the error message if error occurs
	*	Deletes the shader and returns 0
	*	If shader compiles it just returns its ID
*	CompileShaderID
	*	Calls the shaderErrorCheck
	*	Returns the compiled unsigned int ID for the given shader
Texture Class:
*	Generate
	*	Sets the texture parameters wraps and filters parse the images and binds the texture
*	Bind
	*	Binds the texture
	
**VertexElement Struct:**
*	TypeSize
	*	Returns a byte size of a certain data type

**VertexLayout Class:**
*	Add
	*	Adds the vertex element (how much each section is made of e.g. xyz postiton is made up for 3 floats and texture 2 ints.. ect)
	*	Adds to the stride that gets the data type size 
*	GetElements
	*	Returns the vector
*	GetStride
	*	Returns the stride unsigned int
## What makes your program special?
The project was created from scratch however this time lots of knowledge from the previous project (model loader) was utilized and improved upon. The idea to create a Collison trigger system came from general interest in game physics and me wanting to explore that field and understand it more. As checking for collision is one of the first/ important steps to creating a physics system/engine. One of the things that makes my program special is most of the openGL calls has been abstracted out into a more game engine like features with having game objects and applications layers with simple update functions, initialization and a resource manager that caches shaders and textures for more efficient binding and loading. For the physics side of it, one of the unique features is that its very simple and all that user needs to reuse this is to parse in transform (position vector). First simple 2D collider was create just to check if it works with x and y cords, this having less values to work with made it easier to visualize everything and understand it more, once it all worked this was applied to the 3rd axis to create a box collider (collider3D) with a direction check function that returns a vector. These colliders compare to many industry standard physics systems as AABB collisions are used widely across 2D and 3D. These techniques can be adapted to create even more advances colliders such as mesh colliders
