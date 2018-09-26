#include "statisticspage.h"
#include "ui_statisticspage.h"
#include "main.h"
#include "wallet.h"
#include "init.h"
#include "base58.h"
#include "clientmodel.h"
#include "bitcoinrpc.h"
#include <sstream>
#include <string>

using namespace json_spirit;

StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);

    setFixedSize(400, 420);
    ui->startButton->setIcon(QIcon(":/icons/reload"));//
    ui->startButton->setStyleSheet("QPushButton {color: #F8FEFE;background-color: #D56088;border-width: 0px;border-radius: 8px;}");
    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(updateStatistics()));
}

int heightPrevious = -1;
int connectionPrevious = -1;
int volumePrevious = -1;
double netPawratePrevious = -1;
double pawratePrevious = -1;
double hardnessPrevious = -1;
double hardnessPrevious2 = -1;
int stakeminPrevious = -1;
int stakemaxPrevious = -1;
int64_t marketcapPrevious = -1;
QString stakecPrevious = "";
QString rewardPrevious = "";

void StatisticsPage::updateStatistics()
{
    double pHardness = GetDifficulty();
    double pHardness2 = GetDifficulty(GetLastBlockIndex(pindexBest, true));
    int pPawrate = GetPoWMHashPS();
    double pPawrate2 = 0.000;
    int nHeight = pindexBest->nHeight;
    uint64_t nMinWeight = 0, nMaxWeight = 0, nWeight = 0;
    pwalletMain->GetStakeWeight(*pwalletMain, nMinWeight, nMaxWeight, nWeight);
    uint64_t nNetworkWeight = GetPoSKernelPS();
    int64_t volume = ((pindexBest->nMoneySupply)/COIN);
    int peers = this->model->getNumConnections();
    pPawrate2 = (double)pPawrate;
    QString height = QString::number(nHeight);
    QString stakemin = QString::number(nMinWeight);
    QString stakemax = QString::number(nNetworkWeight);
    QString phase = "";
    if (pindexBest->nHeight < LAST_POW_BLOCK)
    {
        phase = "PoW & PoS";
    }
    else if (pindexBest->nHeight > LAST_POW_BLOCK)
    {
        phase = "Proof of Stake";
    }

    QString subsidy = QString("%1 IDOL").arg(QString::number(GetProofOfStakeReward(COIN, 0)/COIN)); // 1 Coin-Day
    QString hardness = QString::number(pHardness, 'f', 6);
    QString hardness2 = QString::number(pHardness2, 'f', 6);
    QString pawrate = QString::number(pPawrate2, 'f', 3);
    QString Qlpawrate = model->getLastBlockDate().toString();

    QString QPeers = QString::number(peers);
    QString qVolume = QString::number(volume);

    if(nHeight > heightPrevious)
    {
        ui->heightBox->setText("<b><font color=\"darkgoldenrod\">" + height + "</font></b>");
    } else {
        ui->heightBox->setText("<b><font color=\"darkorange\">" + height + "</font></b>");
    }

    if(0 > stakeminPrevious)
    {
        ui->minBox->setText("<b><font color=\"darkgoldenrod\">" + stakemin + "</font></b>");
    } else {
        ui->minBox->setText("<b><font color=\"darkorange\">" + stakemin + "</font></b>");
    }
    if(0 > stakemaxPrevious)
    {
        ui->maxBox->setText("<b><font color=\"darkgoldenrod\">" + stakemax + "</font></b>");
    } else {
        ui->maxBox->setText("<b><font color=\"darkorange\">" + stakemax + "</font></b>");
    }

    if(phase != stakecPrevious)
    {
        ui->cBox->setText("<b><font color=\"darkgoldenrod\">" + phase + "</font></b>");
    } else {
        ui->cBox->setText("<b><font color=\"darkorange\">" + phase + "</font></b>");
    }

    if(subsidy != rewardPrevious)
    {
        ui->rewardBox->setText("<b><font color=\"darkgoldenrod\">" + subsidy + "</font></b>");
    } else {
        ui->rewardBox->setText("<b><font color=\"darkorange\">" + subsidy + "</font></b>");
    }

    if(pHardness > hardnessPrevious)
    {
        ui->diffBox->setText("<b><font color=\"darkgoldenrod\">" + hardness + "</font></b>");
    } else if(pHardness < hardnessPrevious) {
        ui->diffBox->setText("<b><font color=\"brown\">" + hardness + "</font></b>");
    } else {
        ui->diffBox->setText("<b><font color=\"darkorange\">" + hardness + "</font></b>");
    }

    // if(marketcap > marketcapPrevious)
    // {
    //     ui->marketcap->setText("<b><font color=\"darkgoldenrod\">$" + QString::number(marketcap) + " USD</font></b>");
    // } else if(marketcap < marketcapPrevious) {
    //     ui->marketcap->setText("<b><font color=\"brown\">$" + QString::number(marketcap) + " USD</font></b>");
    // } else {
    //     ui->marketcap->setText("<b><font color=\"darkorange\">$"+QString::number(marketcap)+" USD</font></b>");
    // }

    if(pHardness2 > hardnessPrevious2)
    {
        ui->diffBox2->setText("<b><font color=\"darkgoldenrod\">" + hardness2 + "</font></b>");
    } else if(pHardness2 < hardnessPrevious2) {
        ui->diffBox2->setText("<b><font color=\"brown\">" + hardness2 + "</font></b>");
    } else {
        ui->diffBox2->setText("<b><font color=\"darkorange\">" + hardness2 + "</font></b>");
    }

    if(pPawrate2 > netPawratePrevious)
    {
        ui->pawrateBox->setText("<b><font color=\"darkgoldenrod\">" + pawrate + " MH/s</font></b>");
    } else if(pPawrate2 < netPawratePrevious) {
        ui->pawrateBox->setText("<b><font color=\"brown\">" + pawrate + " MH/s</font></b>");
    } else {
        ui->pawrateBox->setText("<b><font color=\"darkorange\">" + pawrate + " MH/s</font></b>");
    }

    if(Qlpawrate != pawratePrevious)
    {
        ui->localBox->setText("<b><font color=\"darkgoldenrod\">" + Qlpawrate + "</font></b>");
    } else {
        ui->localBox->setText("<b><font color=\"darkorange\">" + Qlpawrate + "</font></b>");
    }

    if(peers > connectionPrevious)
    {
        ui->connectionBox->setText("<b><font color=\"darkgoldenrod\">" + QPeers + "</font></b>");
    } else if(peers < connectionPrevious) {
        ui->connectionBox->setText("<b><font color=\"brown\">" + QPeers + "</font></b>");
    } else {
        ui->connectionBox->setText("<b><font color=\"darkorange\">" + QPeers + "</font></b>");
    }

    if(volume > volumePrevious)
    {
        ui->volumeBox->setText("<b><font color=\"darkgoldenrod\">" + qVolume + " IDOL" + "</font></b>");
    } else if(volume < volumePrevious) {
        ui->volumeBox->setText("<b><font color=\"brown\">" + qVolume + " IDOL" + "</font></b>");
    } else {
        ui->volumeBox->setText("<b><font color=\"darkorange\">" + qVolume + " IDOL" + "</font></b>");
    }

    //updatePrevious(nHeight, nMinWeight, nNetworkWeight, phase, subsidy, pHardness, pHardness2, pPawrate2, Qlpawrate, peers, volume, marketcap);
}

void StatisticsPage::updatePrevious(int nHeight, int nMinWeight, int nNetworkWeight, QString phase, QString subsidy, double pHardness, double pHardness2, double pPawrate2, QString Qlpawrate, int peers, int volume, int64_t marketcap)
{
    heightPrevious = nHeight;
    stakeminPrevious = nMinWeight;
    stakemaxPrevious = nNetworkWeight;
    stakecPrevious = phase;
    rewardPrevious = subsidy;
    hardnessPrevious = pHardness;
    hardnessPrevious2 = pHardness2;
    netPawratePrevious = pPawrate2;
    pawratePrevious = Qlpawrate;
    connectionPrevious = peers;
    volumePrevious = volume;
    marketcapPrevious = marketcap;
}

void StatisticsPage::setModel(ClientModel *model)
{
    updateStatistics();
    this->model = model;
}


StatisticsPage::~StatisticsPage()
{
    delete ui;
}
