#include "game_loop.h"

// Procesos
void GameLoop::setup() {
	//currentGS->setup();
	sdlGraphics->loadFont( "fonts/advanced_pixel-7.ttf", 50 );
	ss.setup();
	}

void GameLoop::handleInput() {
	
	}

void GameLoop::update() {
	ss.update();
	}

// Wrapper de render
void GameLoop::preRender() {
	// Limpiar pantalla y lo que sea
	sdlGraphics->clearScreen( (const Uint8[]){0x00, 0x11, 0x55, 0xFF} );

	render();

	// Renderizar a pantalla
	sdlGraphics->render();
	}

void GameLoop::render() {
	ss.render( sdlGraphics->getRendererPtr() );
	}

// Constr y Destr
GameLoop::GameLoop() /*: proj(100, 30, 30)*/ {
	if ( !( sdlGraphics = new SDLGraphics() ) ) {
		throw GameLoopException("Insuficiencia de memoria al inicializar SDLGraphics.");
		}
	}

GameLoop::~GameLoop() {
	delete sdlGraphics;
	}

// Loop
void GameLoop::loop() {
	//Event handler
	SDL_Event e;

	// Main loop flag
	bool quit = false;

	setup();

	while ( !quit ) {
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT ) {
				quit = true;
				}
			}

		handleInput();
		update();
		preRender();

		SDL_Delay(1000.0/60.0);
		}
	}
