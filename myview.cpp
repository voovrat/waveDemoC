#include "myview.h"

#include "FL/fl_draw.H"

#include <iostream>

MyView::MyView( AME::SharedObject<MyModel> * model
              , AME::SharedObject<MySettings> * settings 
              )
  : AME::View<MyModel, MySettings>( model, settings )
{
 // dCenterX = 320;
 // dCenterY = 240;

 // dScale = 100;

 // mSettings.tic = 0;
 // saveSettings();

  // TODO
}

MyView::~MyView() 
{
  // TODO
}

void MyView::timer()
{
  mSettings.tic++;
//  std::cout << mSettings.tic;

  saveSettings();
  // e.g. :  syncSettings();
  //  syncModel();
  // TODO	     
}

void MyView::draw() 
{

  // get the model 

  readSettings();
  syncModel();

//    pView->draw();


  

  //draw the view 

  Fl_Offscreen offscreen = fl_create_offscreen(p.w(),p.h());
  fl_begin_offscreen(offscreen); 


  p.init( mModel.Nx, mModel.Ny, mModel.Nz );
  p.clearFields();
  p.addField(&mModel.E(), Color::GREEN );
  p.addField(&mModel.B(), Color::RED );

  p.draw(&mGraph);


 fl_end_offscreen();
 fl_copy_offscreen(100,0,p.w(),p.h(),offscreen,0,0);
 fl_delete_offscreen(offscreen);

}


void MyView::keydown( int key )
{

  switch(key)
  {
    case 'p':
    case ' ':
       OnPause();
       break;

    case 'q':
    case 0xFF1B:  
       OnExit();
       break;

  };

}

void MyView::OnPause( Fl_Widget * sender )
{
  mSettings.paused = !mSettings.paused;
  saveSettings();

  if(!sender) return;
  
  
  if( mSettings.paused )
    sender->label("Resume");
  else
    sender->label("Pause");

}

void MyView::OnExit( Fl_Widget *)
{
  pWnd->hide();  
}