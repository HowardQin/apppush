#include <QApplication.h>
#include "mainformimpl.h"

int main( int argc, char ** argv )
{
	QApplication a( argc, argv );
	mainformImpl w;
	w.show();
	a.connect( &a, SIGNAL( lastWindowClosed() ), &a, SLOT( quit() ) );
	return a.exec();;
}
