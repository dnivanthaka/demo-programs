#include"Screens.h"

Screen::Screen()
{
    running = true;
    x = y = 0;
    screen = SDL_SetVideoMode(1000, 700, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);//screen size
    loadScreen = IMG_Load("media/loadbackground.png");
    play2 = IMG_Load("media/play2.png");
    play = IMG_Load("media/play.png");
    howto = SDL_LoadBMP("media/howto.bmp");
    howto2 = SDL_LoadBMP("media/howto2.bmp");
    guide = SDL_LoadBMP("media/guide.bmp");

    clickFlag = false;
    clickFlag2 = false;
    gameGuide = false;

    playPos = {350, 200, 300, 100};
    playPos2 = {350, 200, 300, 100};

    howtoPos = {350, 325, 300, 100};
    howto2Pos = {350, 325, 300, 100};

    guidePos = {0, 0, 300, 700};
}

bool Screen::loadFirst()//if returns true, means player wants to play
{
    running = true;
    while(running)
    {
        SDL_BlitSurface(loadScreen, NULL, screen, NULL);

        if(SDL_PollEvent(&event))
        {
            if(event.type == SDL_MOUSEMOTION)
            {
                x = event.motion.x;
                y = event.motion.y;
            }

            if(event.type == SDL_QUIT)
            {
                running = false;
                return false;
            }

            //if mouse is within parameters of play button
            if(x>playPos.x && x<playPos.x + playPos.w
               && y < playPos.y + playPos.h && y > playPos.y)
            {

                if( event.type == SDL_MOUSEBUTTONDOWN )
                {
                    //If the left mouse button was pressed
                    if( event.button.button == SDL_BUTTON_LEFT )
                    {
                        SDL_BlitSurface(play2, NULL, screen, &playPos2);
                        SDL_Flip(screen);
                    }
                    clickFlag = true;

                }

                if(event.type == SDL_MOUSEBUTTONUP && clickFlag == true)
                {
                    SDL_BlitSurface(play, NULL, screen, &playPos);
                    SDL_Flip(screen);
                    running = false;
                    clearSurface();
                    return true;

                }
            }

            //if player clicked in the how to region
            else if(x>howtoPos.x && x < howtoPos.x + howtoPos.w
                    && y > howtoPos.y && y < howtoPos.y + howtoPos.h)
            {
                if( event.type == SDL_MOUSEBUTTONDOWN )
                {
                    //If the left mouse button was pressed
                    if( event.button.button == SDL_BUTTON_LEFT )
                    {
                        SDL_BlitSurface(howto2, NULL, screen, &howto2Pos);
                        SDL_Flip(screen);
                    }
                    clickFlag2 = true;

                }

                if(event.type == SDL_MOUSEBUTTONUP && clickFlag2 == true)
                {
                    SDL_BlitSurface(howto, NULL, screen, &howtoPos);
                    runGuide();
                    SDL_Flip(screen);
                    //running = false;
                    //clearSurface();
                    //return true;

                }
            }

            else
            {

                SDL_BlitSurface(play, NULL, screen, &playPos);
                SDL_BlitSurface(howto, NULL, screen, &howtoPos);
                SDL_Flip(screen);
            }

        }//end of event reader

    }//end of while loop


}

void Screen::clearSurface()
{

}


void Screen::runGuide()
{
    SDL_BlitSurface(guide, NULL, screen, &guidePos);
}


/*StringInput::StringInput()
{
    //Initialize the string
    str = "";

    //Initialize the surface
    text = NULL;

    //Enable Unicode
    SDL_EnableUNICODE( SDL_ENABLE );
}

StringInput::~StringInput()
{
    //Free text surface
    SDL_FreeSurface( text );

    //Disable Unicode
    SDL_EnableUNICODE( SDL_DISABLE );
}

void StringInput::handle_input()
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Keep a copy of the current version of the string
        std::string temp = str;

        //If the string less than maximum size
        if( str.length() <= 16 )
        {
                        //If the key is a space
            if( event.key.keysym.unicode == (Uint16)' ' )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }

            //If the key is a number
            else if( ( event.key.keysym.unicode >= (Uint16)'0' ) && ( event.key.keysym.unicode <= (Uint16)'9' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a uppercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'A' ) && ( event.key.keysym.unicode <= (Uint16)'Z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
            //If the key is a lowercase letter
            else if( ( event.key.keysym.unicode >= (Uint16)'a' ) && ( event.key.keysym.unicode <= (Uint16)'z' ) )
            {
                //Append the character
                str += (char)event.key.keysym.unicode;
            }
        }

                //If backspace was pressed and the string isn't blank
        if( ( event.key.keysym.sym == SDLK_BACKSPACE ) && ( str.length() != 0 ) )
        {
            //Remove a character from the end
            str.erase( str.length() - 1 );
        }

                //If the string was changed
        if( str != temp )
        {
            //Free the old surface
            SDL_FreeSurface( text );

            //Render a new text surface
            text = TTF_RenderText_Solid( font, str.c_str(), textColor );
        }
    }
}

void StringInput::show_centered()
{
    //If the surface isn't blank
    if( text != NULL )
    {
        //Show the name
        apply_surface( ( SCREEN_WIDTH - text->w ) / 2, ( SCREEN_HEIGHT - text->h ) / 2, text, screen );
    }
}*/





