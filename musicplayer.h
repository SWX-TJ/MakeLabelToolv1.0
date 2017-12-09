#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QMediaPlayer>
namespace Ui {
class MusicPlayer;
}

class MusicPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit MusicPlayer(QWidget *parent = 0);
    ~MusicPlayer();
public:
    bool isVolumValueSliderVisible;
    bool isPlaySongs;
    int songsIndex;
    QStringList MusicSongList;
    int songsNum;
    QMediaPlayer *m_player;
public slots:
    void dispSongsProcess(qint64);
    void update_durationed(qint64);
private slots:
    void on_VolumeBtn_clicked();
    void on_OpenBtn_clicked();
    void on_StartBtn_clicked();

    void on_PreMusicBtn_clicked();

    void on_NextMusicBtn_clicked();

    void on_VolumeValueSlider_valueChanged(int value);

private:
    Ui::MusicPlayer *ui;
};

#endif // MUSICPLAYER_H
