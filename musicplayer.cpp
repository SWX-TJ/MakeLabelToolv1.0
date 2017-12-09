#include "musicplayer.h"
#include "ui_musicplayer.h"
#include <QDebug>
MusicPlayer::MusicPlayer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MusicPlayer)
{
    ui->setupUi(this);
    isVolumValueSliderVisible = false;
    isPlaySongs = false;
    songsIndex = 0;
    m_player = new QMediaPlayer;
    ui->VolumeValueSlider->setVisible(false);
    connect(m_player,SIGNAL(positionChanged(qint64)),this,SLOT(dispSongsProcess(qint64)));
    connect(m_player,SIGNAL(durationChanged(qint64)),this,SLOT(update_durationed(qint64)));
}

MusicPlayer::~MusicPlayer()
{
    delete ui;
}

void MusicPlayer::dispSongsProcess(qint64 value)
{
    ui->ProcessSlider->setValue(value);
}

void MusicPlayer::update_durationed(qint64 durateValue)
{

    ui->ProcessSlider->setRange(0, durateValue);
    ui->ProcessSlider->setEnabled(durateValue > 0);
    ui->ProcessSlider->setPageStep(durateValue / 10);
}

void MusicPlayer::on_VolumeBtn_clicked()
{
    isVolumValueSliderVisible = !isVolumValueSliderVisible;
    if(isVolumValueSliderVisible)
    {
         ui->VolumeValueSlider->setVisible(true);
    }
    else
    {
        ui->VolumeValueSlider->setVisible(false);
    }
}

void MusicPlayer::on_OpenBtn_clicked()
{
    MusicSongList = QFileDialog::getOpenFileNames(this,"打开音乐","C:/Users/SWX/Music",tr("Music Files (*.mp3 *.wmv)"));
    songsNum = MusicSongList.size();
}

void MusicPlayer::on_StartBtn_clicked()
{
    isPlaySongs = !isPlaySongs;
    if(isPlaySongs)
    {
     ui->StartBtn->setText("stop");
    QString CurrentSongs = MusicSongList.at(songsIndex);
    ui->InfoLabel->setText(CurrentSongs);
    m_player->setMedia(QUrl::fromLocalFile(CurrentSongs));
    m_player->play();
    }
    else
    {
        ui->StartBtn->setText("start");
        m_player->stop();
    }
}

void MusicPlayer::on_PreMusicBtn_clicked()
{
    if(songsIndex<=0)
    {
        songsIndex = songsNum-1;
    }
    songsIndex = songsIndex-1;
    if(songsIndex<=0)
    {
        songsIndex = songsNum-1;
    }
    m_player->stop();
    QString CurrentSongs = MusicSongList.at(songsIndex);
    ui->InfoLabel->setText(CurrentSongs);
    m_player->setMedia(QUrl::fromLocalFile(CurrentSongs));
    m_player->play();

}

void MusicPlayer::on_NextMusicBtn_clicked()
{
    if(songsIndex>=songsNum)
    {
        songsIndex = 0;
    }
    songsIndex = songsIndex+1;
    if(songsIndex>=songsNum)
    {
        songsIndex = 0;
    }
    m_player->stop();
    QString CurrentSongs = MusicSongList.at(songsIndex);
    ui->InfoLabel->setText(CurrentSongs);
    m_player->setMedia(QUrl::fromLocalFile(CurrentSongs));
    m_player->play();
}

void MusicPlayer::on_VolumeValueSlider_valueChanged(int value)
{
    m_player->setVolume(value);
}
