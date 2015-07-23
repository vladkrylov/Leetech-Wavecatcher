#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QElapsedTimer>

#include <stdlib.h>

#include <TCanvas.h>
#include <TVirtualX.h>
#include <TSystem.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TGraph.h>
#include <TFrame.h>
#include <TTimer.h>

#include "canvas.h"
#include "wavecatcher.h"

//------------------------------------------------------------------------------

//______________________________________________________________________________
QRootCanvas::QRootCanvas(QWidget *parent) : QWidget(parent, 0), fCanvas(0)
{
   // QRootCanvas constructor.

   // set options needed to properly update the canvas when resizing the widget
   // and to properly handle context menus and mouse move events
//   setAttribute(Qt::WA_PaintOnScreen, true);
//   setAttribute(Qt::WA_OpaquePaintEvent, true);
   setMinimumSize(300, 200);
   setUpdatesEnabled(kFALSE);
   setMouseTracking(kTRUE);

   // register the QWidget in TVirtualX, giving its native window id
   int wid = gVirtualX->AddWindow((ULong_t)winId(), 600, 400);
   // create the ROOT TCanvas, giving as argument the QWidget registered id
   fCanvas = new TCanvas("Root Canvas", width(), height(), wid);
}

//______________________________________________________________________________
void QRootCanvas::mouseMoveEvent(QMouseEvent *e)
{
   // Handle mouse move events.

   if (fCanvas) {
      if (e->buttons() & Qt::LeftButton) {
         fCanvas->HandleInput(kButton1Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::MidButton) {
         fCanvas->HandleInput(kButton2Motion, e->x(), e->y());
      } else if (e->buttons() & Qt::RightButton) {
         fCanvas->HandleInput(kButton3Motion, e->x(), e->y());
      } else {
         fCanvas->HandleInput(kMouseMotion, e->x(), e->y());
      }
   }
}

//______________________________________________________________________________
void QRootCanvas::mousePressEvent( QMouseEvent *e )
{
   // Handle mouse button press events.

   if (fCanvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            fCanvas->HandleInput(kButton1Down, e->x(), e->y());
            break;
         case Qt::MidButton :
            fCanvas->HandleInput(kButton2Down, e->x(), e->y());
            break;
         case Qt::RightButton :
            // does not work properly on Linux...
            // ...adding setAttribute(Qt::WA_PaintOnScreen, true)
            // seems to cure the problem
            fCanvas->HandleInput(kButton3Down, e->x(), e->y());
            break;
         default:
            break;
      }
   }
}

//______________________________________________________________________________
void QRootCanvas::mouseReleaseEvent( QMouseEvent *e )
{
   // Handle mouse button release events.

   if (fCanvas) {
      switch (e->button()) {
         case Qt::LeftButton :
            fCanvas->HandleInput(kButton1Up, e->x(), e->y());
            break;
         case Qt::MidButton :
            fCanvas->HandleInput(kButton2Up, e->x(), e->y());
            break;
         case Qt::RightButton :
            // does not work properly on Linux...
            // ...adding setAttribute(Qt::WA_PaintOnScreen, true)
            // seems to cure the problem
            fCanvas->HandleInput(kButton3Up, e->x(), e->y());
            break;
         default:
            break;
      }
   }
}

//______________________________________________________________________________
void QRootCanvas::resizeEvent( QResizeEvent * )
{
   // Handle resize events.

   if (fCanvas) {
      fCanvas->Resize();
      fCanvas->Update();
   }
}

//______________________________________________________________________________
void QRootCanvas::paintEvent( QPaintEvent * )
{
   // Handle paint events.

   if (fCanvas) {
      fCanvas->Resize();
      fCanvas->Update();
   }
}

//------------------------------------------------------------------------------

//______________________________________________________________________________
QMainCanvas::QMainCanvas(QWidget *parent) : QWidget(parent),
    N_HORIZONTAL_DIVISIONS(16),
    N_VERTICAL_DIVISIONS(9)
{
   // QMainCanvas constructor.

   QVBoxLayout *l = new QVBoxLayout(this);
   l->addWidget(canvas = new QRootCanvas(this));
   canvas->getCanvas()->SetGrid();
   canvas->getCanvas()->Pad()->SetGrid();

   h = 900;
   for (int ch = 0; ch < N_CHANNELS; ++ch) {
       gr[ch] = new TGraph();
       gr[ch]->SetLineColor(ch+1);

       scales[ch] = 1;
       enabled[ch] = true;
   }
   gr[0]->SetLineColor(46);
}

//void QMainCanvas::handle_root_events()
//{
//   //call the inner loop of ROOT
//   gSystem->ProcessEvents();
//}

void QMainCanvas::changeEvent(QEvent * e)
{
//   if (e->type() == QEvent ::WindowStateChange) {
//      QWindowStateChangeEvent * event = static_cast< QWindowStateChangeEvent * >( e );
//      if (( event->oldState() & Qt::WindowMaximized ) ||
//          ( event->oldState() & Qt::WindowMinimized ) ||
//          ( event->oldState() == Qt::WindowNoState &&
//            this->windowState() == Qt::WindowMaximized )) {
//         if (canvas->getCanvas()) {
//            canvas->getCanvas()->Resize();
//            canvas->getCanvas()->Update();
//         }
//      }
//   }
}

void QMainCanvas::DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData)
{
    QElapsedTimer eltim;
    eltim.start();

//    int size = ChannelData[0].WaveformDataSize;

    canvas->getCanvas()->Clear();
//    canvas->getCanvas()->cd();
//    canvas->getCanvas()->SetBorderMode(0);
//    canvas->getCanvas()->SetFillColor(0);
//    canvas->getCanvas()->SetGrid();

//    gr[0]->Set(size);
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        if (enabled[ch]) {
            for (int i = 0; i < xMaxInd-xMinInd; ++i) {
                gr[ch]->Clear();
                gr[ch]->Set(xMaxInd-xMinInd);
                gr[ch]->SetPoint(i, i + xMinInd,
                                  WAVECAT64CH_ADCTOVOLTS * 1000 * h/N_VERTICAL_DIVISIONS /scales[ch] * ChannelData[ch].WaveformData[i+xMinInd] + baselines[ch] * h / 100.);
            }
        }
    }

    // draw first enabled channel
    int drawn = -1;
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        if (enabled[ch]) {
            gr[ch]->SetFillColor(kViolet + 2);
            gr[ch]->SetFillStyle(3001);
            gr[ch]->GetXaxis()->SetLimits(xMinInd, xMaxInd);
            gr[ch]->GetXaxis()->SetLabelSize(0);
            gr[ch]->GetXaxis()->SetNdivisions(N_HORIZONTAL_DIVISIONS, false);
            gr[ch]->GetYaxis()->SetNdivisions(N_VERTICAL_DIVISIONS, false);
            gr[ch]->GetYaxis()->SetLabelSize(0);
            gr[ch]->SetMaximum(h);
            gr[ch]->SetMinimum(0);

            gr[ch]->Draw();
            drawn = ch;
            break;
        }
    }
    // draw other channels
    for (int ch = 0; ch < N_CHANNELS; ++ch) {
        if ((enabled[ch]) && (drawn != ch)) gr[ch]->Draw("same");
    }

    canvas->getCanvas()->Modified();
    canvas->getCanvas()->Resize();
    canvas->getCanvas()->Update();

//    qDebug() << eltim.elapsed();
}


