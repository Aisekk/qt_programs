#include <QApplication>
#include "SoundPlayer.h"
#include "VideoPlayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SoundPlayer soundPlayer;
    soundPlayer.resize(320,75);
    soundPlayer.show();

    VideoPlayer videoPlayer;
    videoPlayer.resize(400,450);
    videoPlayer.show();

    return a.exec();
}
