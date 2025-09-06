# mesh
- creating a mesh to draw
- call mesh::create() + mesh::setup() in game::setup()
- call mesh::nuke() in game::shutdown();
- call mesh::draw() in game::render()

- it have 2 functions to override
  * clean() for extra clean (if needed) when more data is added to a derived class from mesh
  * setup() used primarily set attributes for certain vertex type after calling glVertexArrayVertexBuffer.
