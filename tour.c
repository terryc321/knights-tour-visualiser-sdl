
/*

  knights tour visualisation tool

  1. stability
  if chessboard image or knight image is missing program falls over
  if proggy font missing program falls over

  
  given a text file with numbers

  1 1 1   means piece 1 at column 1 row 1

  2 2 3   means piece 2 at column 2 row 3

  so on ...

  when knight backtracks it will add more data

  we may get to a state like
  
  2 1 5  means piece 2 has moved to a different position

  so visualizer can highlight this transition if it so wishes

  visualizer should be able to move forwards and backwards arbitrarily fast ?

  cant jump to end , that be turing breaking software

  --------------------------------------------------------------------
  
  originally all knights are off the board

  so user cannot see them

  if user changes window size , graphics need to adjust for this so having fixed

  pixel coordinates does not make any sense

    --------------------------------------------------------------------

  looking at fastest way to get chunk data on file into memory

  looking at fastest way to display that data to screen

  optimium size buffer read / write

  ultimately still need to compute next position unless have stations 

  --------------------------------------------------------------------

   station is a state where everything is known to continue forward

   example horses 1 to 10 have these positions , your current position horse 10
   is at X , Y

   now proceed with the knights tour

   --------------------------------------------------------------------

   station cannot allow us to always go backwards because we would have to know

   the entire history of computation 
   
   
   --------------------------------------------------------------------

    
 */





#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// for errno include errno.h
#include <errno.h>

// for sleep include unistd.h
#include<unistd.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

// now need sdl image
#include <SDL2/SDL_image.h>

// fonts
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mouse.h>

// mouse motion etc..
#include <SDL2/SDL_events.h>

FILE *fp;

void render_text(
    SDL_Renderer *renderer,
    int x,
    int y,
    const char *text,
    TTF_Font *font,
    SDL_Rect *rect,
    SDL_Color *color
) {
    SDL_Surface *surface;
    SDL_Texture *texture;

    surface = TTF_RenderText_Solid(font, text, *color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->x = x;
    rect->y = y;
    rect->w = surface->w;
    rect->h = surface->h;
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, rect);
    SDL_DestroyTexture(texture);
}


void screenXY(int b, int c , int *pixel_x , int *pixel_y);
void screenXY(int b, int c , int *pixel_x , int *pixel_y){
         *pixel_x = 40 + (b - 1) * 118 ;
         *pixel_y = 249 + (8 - c)*90;
}




int main(int argc, char *argv[])
{
  printf("program received %d arguments \n",argc);  
  printf("name of program ? : %s\n",argv[0]);
  if (argc < 2)
    {
      fprintf(stderr,"plese provide the tour file to follow\n");
      exit(1);
    }

  printf("filenmae = %s\n",argv[1]);
  
  
  fp = fopen(argv[1], "r");
  if (!fp || errno){
    fprintf(stderr,"file [%s] cannot be found\n",argv[1]);
    exit(2);    
  }
  

  // do file handles get closed automatically? - posix says yes
  //fclose(fp);
  
      
       int mouse_x = 0 ;
       int mouse_y = 0;
  
       // returns zero on success else non-zero
       if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Window* win = SDL_CreateWindow("GAME", // creates a window
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    1000, 1000, 0);

    // triggers the program that controls
    // your graphics hardware and sets flags
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;

    // creates a renderer to render our images
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    ///
    /// Section 2: SDL image loader
    ///
///
    /// Section 2: SDL image loader
    ///

    // creates a surface to load an image into the main memory
    // please provide a path for your image
    SDL_Surface* surface = IMG_Load("./chessboard-empty.png");
    // loads image to our graphics hardware memory.
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    // clears main-memory
    SDL_FreeSurface(surface);


    // suppose moving a piece on board
    int i = 0;
    SDL_Rect rect2[100];
    SDL_Texture* tex2[100];    
    //SDL_Surface* surface2 = IMG_Load("../images/white-pawn.png");
    SDL_Surface* surface2 = IMG_Load("./white-knight.png");
    for (i = 0 ; i < 100; i++){
      tex2[i] = SDL_CreateTextureFromSurface(rend, surface2);
      rect2[i].x = 0;
      rect2[i].y = 0;
      rect2[i].w = surface2->w;
      rect2[i].h = surface2->h;
    }
    SDL_FreeSurface(surface2);   

    
    // let us control our image position
    // so that we can move it with our keyboard.
    SDL_Rect dest;
    // connects our texture with dest to control position
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // connect piece to mouse x y ??
    //SDL_QueryTexture(tex2, NULL, NULL ,&mouse_x, &mouse_y);


    
    // adjust height and width of our image box.
    /* dest.w *= 2; */
    /* dest.h *= 2; */

    // sets initial x-position of object
    //dest.x = (1000 - dest.w) / 2;

    // sets initial y-position of object
    //dest.y = (1000 - dest.h) / 2;
    dest.x = 0;
    dest.y = 0;
    dest.w = 1000;
    dest.y = 1000;
    

    ///
    /// Section 4: SDL ttf and rendering text
    ///

 // Init TTF
    TTF_Init();

    // in font-manager on console , find true type fonts on left side widget Filetype
    // once find font like , can right click on style of font like regular
    // show in location
    // opens file folder where that font located

    
    //TTF_Font *font = TTF_OpenFont("Roboto-Regular.ttf", 24);
    TTF_Font *font = TTF_OpenFont("./ProggyClean.ttf", 40);
    if (font == NULL) {
        printf("error initializing TTF: %s\n", TTF_GetError());
        return 1;
    }

    // set relative mouse mode ..
    //SDL_SetRelativeMouseMode(1); 

    // grab keyboard
    //SDL_SetWindowKeyboardGrab(win,1);

    // grab window
    //SDL_SetWindowGrab(win,1);
    
    ///
    /// Section 3: Game Loop and Basic Controls
    ///     Note: The rest of this snippet will be removed
// controls animation loop
    int close = 0;

    // speed of box
    int speed = 300;

    // set mouse initial position say 500 500
    mouse_x = 500; mouse_y = 400;
    //SDL_color color1 = mk_SDL_Color(255,255,0);
    SDL_Color color1 = { 255, 0, 0 };
    SDL_Color color2 = { 0, 0, 255 };

    int delay = 0;
    int delay_limit = 500;
    int last_knight = 1;
    
    // animation loop
    while (!close) {
        SDL_Event event;

        // Events management
        while (SDL_PollEvent(&event)) {
            switch (event.type) {

	      
	    case SDL_MOUSEMOTION:
	      // x y coorrds relative to window
	      mouse_x = event.motion.x; 	
	      mouse_y = event.motion.y; 
      
	      break;
	      
            case SDL_QUIT:
                // handling of close button
                close = 1;
                break;

            case SDL_KEYDOWN:
                // keyboard API for key pressed
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_ESCAPE:
                    close = 1;
                    break;
                case SDL_SCANCODE_W:
		  delay_limit --;
		  if (delay_limit < 0){
		    delay_limit = 0;
		  }
		  break;
		case SDL_SCANCODE_KP_PLUS:
		  dest.w = dest.w + 10;
		  dest.h = dest.h + 10;		  
		  break;
		case SDL_SCANCODE_KP_MINUS:
		  dest.w = dest.w - 10;
		  dest.h = dest.h - 10;
		  break;
		  
                case SDL_SCANCODE_UP:
		  //dest.y -= speed / 30;
		  
                    break;
                case SDL_SCANCODE_A:
		  break;
                case SDL_SCANCODE_LEFT:
                    dest.x -= speed / 30;
                    break;
                case SDL_SCANCODE_S:
		  delay_limit ++;
		  break;
                case SDL_SCANCODE_DOWN:
		  //dest.y += speed / 30;
                    break;
                case SDL_SCANCODE_D:
		  break;
                case SDL_SCANCODE_RIGHT:
                    dest.x += speed / 30;
                    break;
                default:
                    break;
                }
            }
        }

        // right boundary
        if (dest.x + dest.w > 1000)
            dest.x = 1000 - dest.w;

        // left boundary
        if (dest.x < 0)
            dest.x = 0;

        // bottom boundary
        if (dest.y + dest.h > 1000)
            dest.y = 1000 - dest.h;

        // upper boundary
        if (dest.y < 0)
            dest.y = 0;

	//printf("dest w/h = %d , %d\n" ,dest.w , dest.h);
	
        // clears the screen - white color
	SDL_SetRenderDrawColor(rend, 0,255,255,0); //white
	
        SDL_RenderClear(rend);
	// color
	SDL_SetRenderDrawColor(rend, 0,0,255,0); //blue
	
        SDL_RenderCopy(rend, tex, NULL, &dest);

	
	/*
	int i = 0;	
	for (i= 0 ;i < 10; i++){
	  SDL_RenderCopy(rend, tex2, NULL, &rect2);	  
	  rect2.x += 10;
	  SDL_RenderCopy(rend, tex2, NULL, &rect2);
	  rect2.x += 10;
	  SDL_RenderCopy(rend, tex2, NULL, &rect2);
	  rect2.x += 10;
	  sleep(1);
	  }*/

	delay ++;
	//printf("%d  \r" , delay);
	
        int a, b , c;
	if (delay > delay_limit){

	  delay = 0;
	  
	if (feof(fp)){
	  fprintf(stderr,"file end of file\n");
	  fprintf(stderr,"exiting...\n");
	  exit(5);
	}
	else {
	fscanf(fp,"%d",&a);
	fscanf(fp,"%d",&b);
	fscanf(fp,"%d",&c);	
	// 1 1 1
	// piece 1 at row 1 column 1
	// in terms of display may be hundreds
	//
	//                                    |
	// Y increases top down screen       \|/
	//                                    .   +Y dir
	//
	// X increases from left to right -> + X dir
	if (a >= 0 && a < 100){
	  // rect2 want PIXELS rather than CHESS BOARD LOCATIONS
	  // last knight is read as a
	  last_knight = a;
	  // meaning , may have backtracked , be some knights higher up from old
	  // search tree
	  int pixel_x , pixel_y ;
	  screenXY(b,c,&pixel_x, &pixel_y);
	  rect2[a].x = pixel_x; //40 + (b - 1) * 118 ;
	  rect2[a].y = pixel_y; //249 + (8 - c)*90;
	}
	else {
	  fprintf(stderr,"encoding error or end of file\n");
	  fprintf(stderr,"got data piece %d : column %d : row %d \n",a,b,c);
	  fprintf(stderr,"exiting...\n");
	  //sleep(10);
	  //exit(4);
	}
	}
	
	} // delay
	
	int x = 0;
	int y = 0;
	int j = 0;
	for(i = 1;i <= last_knight; i ++){	  
	  SDL_RenderCopy(rend, tex2[i], NULL, &rect2[i]);
	}

	
	// --------- KNIGHTS PATH  LINE DRAWING --------------------
	for (i = 1 ; i < last_knight; i ++){
	  int ax , ay ;
	  int bx , by ;
	  ax = rect2[i].x;
	  ay = rect2[i].y;
	  bx = rect2[i+1].x;
	  by = rect2[i+1].y;		    
	  for (j = 1 ; j <= last_knight; j ++){
	    int adjust_x = 53;
	    int adjust_y = 50;
	    SDL_RenderDrawLine(rend,
			       ax + adjust_x ,ay + adjust_y,
			       bx + adjust_x , by + adjust_y);
	  }
	}
				   

	
	
	// maybe draw lines
	
	
       ///
       /// Section 4: SDL ttf and rendering text
       ///

	// create a rectangle to update with the size of the rendered text
        SDL_Rect text_rect;

        // The color for the text we will be displaying
        SDL_Color white = {255, 255, 255, 0};

        // so we can have nice text, two lines one above the next
	SDL_SetRenderDrawColor(rend, 0,255,0,0); //green
	// render_text(rend, 10, 10, "Hello World!", font, &text_rect, &white);
	render_text(rend, 10, 10, "Hello World!", font, &text_rect, &color1);

	char message[100];
	//
	SDL_SetRenderDrawColor(rend, 255,0,255,0); //red+green
	sprintf(message,"Mouse(%d,%d):Dlim(%d)",mouse_x , mouse_y, delay_limit);
        render_text(rend, 10, text_rect.y + 0.5*text_rect.h, message, font, &text_rect, &color2);

	

	// get mouse
	//SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
	SDL_SetRenderDrawColor(rend, 125,125,255,0); //red+green+blue?

	// cross hair size
	int csz = 10; 
	SDL_RenderDrawLine(rend, mouse_x - csz ,mouse_y , mouse_x + csz, mouse_y);
	SDL_RenderDrawLine(rend, mouse_x  ,mouse_y - csz , mouse_x  , mouse_y + csz);

	/*
	SDL_RenderDrawLine(rend, 300 ,50 , mouse_x , mouse_y);
	SDL_RenderDrawLine(rend, 50 ,400 , mouse_x , mouse_y);
	SDL_RenderDrawLine(rend, 500 ,700 , mouse_x , mouse_y);
	SDL_RenderDrawLine(rend, 600 ,200 , mouse_x , mouse_y);
	*/
	
        // triggers the double buffers
        // for multiple rendering	
        SDL_RenderPresent(rend);

	
        // calculates to 60 fps
        //SDL_Delay(1000 / 60);

	
    }

    ///
    /// Section 3: Game Loop and Basic Controls
    ///     Note: The code above will be removed

    ///
    /// Section 5: Freeing resources
    ///
   // close font handle
    TTF_CloseFont(font);

    // close TTF
    TTF_Quit();

    // destroy texture
    SDL_DestroyTexture(tex);

    // destroy renderer
    SDL_DestroyRenderer(rend);
    
    // We add a delay in order to see that our window
    // has successfully popped up.
    //SDL_Delay(3000);

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(win);
    
    // We safely uninitialize SDL2, that is, we are
    // taking down the subsystems here before we exit
    // our program.
    SDL_Quit();
}


