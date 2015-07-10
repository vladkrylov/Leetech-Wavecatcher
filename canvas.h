
#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QWidget>
#include "wavecatcher.h"

class QPaintEvent;
class QResizeEvent;
class QMouseEvent;
class QTimer;
class TCanvas;
class TGraph;

class QRootCanvas : public QWidget
{
   Q_OBJECT

public:
   QRootCanvas( QWidget *parent = 0);
   virtual ~QRootCanvas() {}
   TCanvas* getCanvas() { return fCanvas;}

protected:
   TCanvas        *fCanvas;

   virtual void    mouseMoveEvent( QMouseEvent *e );
   virtual void    mousePressEvent( QMouseEvent *e );
   virtual void    mouseReleaseEvent( QMouseEvent *e );
   virtual void    paintEvent( QPaintEvent *e );
   virtual void    resizeEvent( QResizeEvent *e );
};

class QMainCanvas : public QWidget
{
   Q_OBJECT

public:
   QMainCanvas( QWidget *parent = 0);
   virtual ~QMainCanvas() {}
   virtual void changeEvent(QEvent * e);

   const int N_HORIZONTAL_DIVISIONS;
   const int N_VERTICAL_DIVISIONS;

   bool enabled[N_CHANNELS];
   float baselines[N_CHANNELS];
   float scales[N_CHANNELS];

   int xMinInd;
   int xMaxInd;


public slots:
//   void handle_root_events();
   void DrawWaveforms(const WAVECAT64CH_ChannelDataStruct* ChannelData);

private:
   TGraph* gr[N_CHANNELS];

   float h;



protected:
   QRootCanvas    *canvas;
   QTimer         *fRootTimer;
};

#endif


