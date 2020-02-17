#include "vnccli.h"
#include <QObject>
#include <QImage>
#include <QPainter>

VncCli::VncCli(QObject * parent):QObject(parent)
{

}

void VncCli::doWork()
{
    while(1) {

                  cl=rfbGetClient(8,3,4);
                //cl->MallocFrameBuffer=resize;
                  cl->canHandleNewFBSize = TRUE;
                 //cl->GotFrameBufferUpdate=update;
                  //cl->HandleKeyboardLedState=kbd_leds;
                  //cl->HandleTextChat=text_chat;
                  //cl->GotXCutText = got_selection;
                  cl->GetCredential = get_credential;
                  cl->listenPort = LISTEN_PORT_OFFSET;
                  cl->listen6Port = LISTEN_PORT_OFFSET;
        //wykonuj petle zdarzen

    }
}

 rfbBool VncCli::resize(rfbClient* client) {
    int width=client->width,height=client->height,
        depth=client->format.bitsPerPixel;

    //if (enableResizable)
     //   sdlFlags |= SDL_WINDOW_RESIZABLE;

    client->updateRect.x = client->updateRect.y = 0;
    client->updateRect.w = width; client->updateRect.h = height;
    /* copdth; client->updateRect.h = height;

    /* (re)create the surface used as the client's framebuffer */
    //SDL_FreeSurface(rfbClientGetClientData(client, SDL_Init));
    //SDL_Surface* sdl=SDL_CreateRGBSurface(0,
                         // width,
                         // height,
                         // depth,
                        //  0,0,0,0);
    //if(!sdl)
      //  rfbClientErr("resize: error creating surface: %s\n", SDL_GetError());

    //rfbClientSetClientData(client, SDL_Init, sdl);
    //client->width = sdl->pitch / (depth / 8);
  //  client->frameBuffer=sdl->pixels;

  //  client->format.bitsPerPixel=depth;
   // client->format.redShift=sdl->format->Rshift;
   // client->format.greenShift=sdl->format->Gshift;
   // client->format.blueShift=sdl->format->Bshift;
   // client->format.redMax=sdl->format->Rmask>>client->format.redShift;
   // client->format.greenMax=sdl->format->Gmask>>client->format.greenShift;
   // client->format.blueMax=sdl->format->Bmask>>client->format.blueShift;
   // SetFormatAndEncodings(client);

    /* create or resize the window */
    //if(!sdlWindow) {
     //   sdlWindow = SDL_CreateWindow(client->desktopName,
        //			 SDL_WINDOWPOS_UNDEFINED,
        //			 SDL_WINDOWPOS_UNDEFINED,
        //			 width,
            //		 height,
            //		 sdlFlags);
     //   if(!sdlWindow)
    //	rfbClientErr("resize: error creating window: %s\n", SDL_GetError());
    //} else {
    //    SDL_SetWindowSize(sdlWindow, width, height);
    //}

    /* create the renderer if it does not already exist */
    //if(!sdlRenderer) {
    //    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, 0);
     //   if(!sdlRenderer)
    //	rfbClientErr("resize: error creating renderer: %s\n", SDL_GetError());
     //   SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  /* make the scaled rendering look smoother. */
  //  }
    //SDL_RenderSetLogicalSize(sdlRenderer, width, height);  /* this is a departure from the SDL1.2-based version, but more in the sense of a VNC viewer in keeeping aspect ratio */

    /* (re)create the texture that sits in between the surface->pixels and the renderer */
//	if(sdlTexture)
    //    SDL_DestroyTexture(sdlTexture);
    //sdlTexture = SDL_CreateTexture(sdlRenderer,
                     //  SDL_PIXELFORMAT_ARGB8888,
                     //  SDL_TEXTUREACCESS_STREAMING,
                     //  width, height);
    //if(!sdlTexture)
        std::cerr<<("resize: error creating texture: %s\n");
    return TRUE;
}
void VncCli::update(rfbClient* cl,int x,int y,int w,int h) {

   // SDL_Surface *sdl = rfbClientGetClientData(cl, SDL_Init);
   QImage * img = (QImage*)rfbClientGetClientData(cl, 0);
    /* update texture from surface->pixels */
   // SDL_Rect r = {x,y,w,h};
   QRect r = {x, y, w, h};
   // if(SDL_UpdateTexture(sdlTexture, &r, sdl->pixels + y*sdl->pitch + x*4, sdl->pitch) < 0)
      //sdlupdatetexture aktualizyuje dana teksture z okreslonym kawalkiem okienka
   std::cout<<("update: failed to update texture: %s\n");
//if ()
QPainter paint;
paint.begin(img);
        /* copy texture to renderer and show */
   // if(SDL_RenderClear(sdlRenderer) < 0)
         std::cout<<("update: failed to clear renderer: %s\n");
   // if(SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL) < 0)
         std::cout<<("update: failed to copy texture to renderer: %s\n");
   // SDL_RenderPresent(sdlRenderer);
}


 rfbCredential* VncCli::get_credential(rfbClient* cl, int credentialType){
        rfbCredential *c = (rfbCredential*)malloc(sizeof(rfbCredential));
    c->userCredential.username = (char*)malloc(RFB_BUF_SIZE);
    c->userCredential.password = (char*)malloc(RFB_BUF_SIZE);

    if(credentialType != rfbCredentialTypeUser) {
        std::cout<<("something else than username and password required for authentication\n");
        return NULL;
    }

    std::cout<<("username and password required for authentication!\n");
    printf("user: ");
    fgets(c->userCredential.username, RFB_BUF_SIZE, stdin);
    printf("pass: ");
    fgets(c->userCredential.password, RFB_BUF_SIZE, stdin);

    /* remove trailing newlines */
    c->userCredential.username[strcspn(c->userCredential.username, "\n")] = 0;
    c->userCredential.password[strcspn(c->userCredential.password, "\n")] = 0;

    return c;
}


 void VncCli::doSetup(QThread & thread)
 {
 QObject::connect(&thread, SIGNAL(started()),this, SLOT(doWork()));
 }
