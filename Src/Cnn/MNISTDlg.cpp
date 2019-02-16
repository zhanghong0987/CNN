#include "MNISTDlg.h"
#include "ReadMNIST.h"

#include <QFileDialog>
#include <QLabel>
#include <QSettings>

QMNISTDlg::QMNISTDlg(QWidget *parent)
	: QDialog(parent)
	, m_pData(NULL)
	, m_count(0)
{
	ui.setupUi(this);

	m_sIniFile = QCoreApplication::applicationDirPath() + "/MNIST.ini";
	m_nImage = 100;
	m_arrWidgetImage = new QLabel*[m_nImage];
	m_arrWidgetLabel = new QLabel*[m_nImage];

	for (int i = 0; i < m_nImage; i++)
	{
		m_arrWidgetImage[i] = new QLabel(ui.widget_image);
		m_arrWidgetImage[i]->setObjectName(QStringLiteral("widget_image_%1").arg(i));
		m_arrWidgetImage[i]->setMinimumSize(QSize(28, 28));
		m_arrWidgetImage[i]->setMaximumSize(QSize(28, 28));
		m_arrWidgetImage[i]->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
		ui.gridLayout_image->addWidget(m_arrWidgetImage[i], i / 10, i % 10, 1, 1);

		m_arrWidgetLabel[i] = new QLabel(ui.widget_label);
		m_arrWidgetLabel[i]->setObjectName(QStringLiteral("widget_label_%1").arg(i));
		m_arrWidgetLabel[i]->setMinimumSize(QSize(28, 28));
		m_arrWidgetLabel[i]->setMaximumSize(QSize(28, 28));
		//m_arrWidgetLabel[i]->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
		ui.gridLayout_label->addWidget(m_arrWidgetLabel[i], i / 10, i % 10, 1, 1);

	}
}

QMNISTDlg::~QMNISTDlg()
{
	delete[] m_arrWidgetImage; m_arrWidgetImage = NULL;
	delete[] m_arrWidgetLabel; m_arrWidgetLabel = NULL;
	delete[] m_pData;
}

void QMNISTDlg::on_btnOpen_clicked()
{
	QSettings setting(m_sIniFile, QSettings::IniFormat);
	QString sImageFile = setting.value("ImageFile").toString();
	QString sLabelFile = setting.value("LabelFile").toString();

	sImageFile = QFileDialog::getOpenFileName(this, tr("Open Image File"), sImageFile, tr("MNIST Image File(*.*)"));
	if (sImageFile.length() == 0) return;
	
	sLabelFile = QFileDialog::getOpenFileName(this, tr("Open Label File"), sLabelFile, tr("MNIST Label File(*.*)"));
	if (sLabelFile.length() == 0) return;

	setting.setValue("ImageFile", sImageFile);
	setting.setValue("LabelFile", sLabelFile);

	if(m_pData) delete[] m_pData;
	mnist_load(
		sImageFile.toStdString().c_str(),
		sLabelFile.toStdString().c_str(),
		&m_pData,
		&m_count);

	ui.scrollBar->setRange(0, m_count - 100);
	ui.scrollBar->setValue(0);
	Repaint(0);
}

void QMNISTDlg::on_scrollBar_actionTriggered(int action)
{
	int k = ui.scrollBar->sliderPosition();
	switch (action)
	{
	case QAbstractSlider::SliderSingleStepAdd:
	case QAbstractSlider::SliderSingleStepSub:
	case QAbstractSlider::SliderPageStepAdd:
	case QAbstractSlider::SliderPageStepSub:
		Repaint(k);
		break;
	default:
		break;
	}
}

void QMNISTDlg::on_scrollBar_sliderMoved(int k)
{
	Repaint(k);
}

void QMNISTDlg::Repaint(int k)
{
	if (!m_pData) return;

	ui.labelRange->setText(QString("%1-%2").arg(k).arg(k + 99));

	for (int i = 0; i < m_nImage; i++)
	{
		QImage image((unsigned char*)(m_pData[i + k].data), 28, 28, QImage::Format_Grayscale8);
		QPixmap pix(28, 28);
		pix.convertFromImage(image);
		m_arrWidgetImage[i]->setPixmap(pix);
		m_arrWidgetLabel[i]->setText(QString("%1").arg(m_pData[i + k].label));
	}
}
