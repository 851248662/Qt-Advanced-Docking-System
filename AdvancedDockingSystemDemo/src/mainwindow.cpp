#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QLabel>
#include <QTextEdit>
#include <QCalendarWidget>
#include <QFrame>
#include <QTreeView>
#include <QFileSystemModel>

#include "ads/ContainerWidget.h"
#include "ads/SectionWidget.h"
#include "ads/SectionContent.h"

#include "LayoutManagerWidget.h"

#include "icontitlewidget.h"

///////////////////////////////////////////////////////////////////////

static int CONTENT_COUNT = 0;

static ADS_NS::SectionContent::RefPtr createLongTextLabelSC(ADS_NS::ContainerWidget* container)
{
	QWidget* w = new QWidget();
	QBoxLayout* bl = new QBoxLayout(QBoxLayout::TopToBottom);
	w->setLayout(bl);

	QLabel* l = new QLabel();
	l->setWordWrap(true);
	l->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	l->setText(QString("Lorem Ipsum ist ein einfacher Demo-Text für die Print- und Schriftindustrie. Lorem Ipsum ist in der Industrie bereits der Standard Demo-Text seit 1500, als ein unbekannter Schriftsteller eine Hand voll Wörter nahm und diese durcheinander warf um ein Musterbuch zu erstellen. Es hat nicht nur 5 Jahrhunderte überlebt, sondern auch in Spruch in die elektronische Schriftbearbeitung geschafft (bemerke, nahezu unverändert). Bekannt wurde es 1960, mit dem erscheinen von Letrase, welches Passagen von Lorem Ipsum enhielt, so wie Desktop Software wie Aldus PageMaker - ebenfalls mit Lorem Ipsum."));
	bl->addWidget(l);

	const int index = ++CONTENT_COUNT;
	return ADS_NS::SectionContent::newSectionContent(QString("uname-%1").arg(index), container, new IconTitleWidget(QIcon(), QString("Label %1").arg(index)), w);
}

static ADS_NS::SectionContent::RefPtr createCalendarSC(ADS_NS::ContainerWidget* container)
{
	QCalendarWidget* w = new QCalendarWidget();

	const int index = ++CONTENT_COUNT;
	return ADS_NS::SectionContent::newSectionContent(QString("uname-%1").arg(index), container, new IconTitleWidget(QIcon(), QString("Calendar %1").arg(index)), w);
}

static ADS_NS::SectionContent::RefPtr createFileSystemTreeSC(ADS_NS::ContainerWidget* container)
{
	QTreeView* w = new QTreeView();
	//	QFileSystemModel* m = new QFileSystemModel(w);
	//	m->setRootPath(QDir::currentPath());
	//	w->setModel(m);

	const int index = ++CONTENT_COUNT;
	return ADS_NS::SectionContent::newSectionContent(QString("uname-%1").arg(index), container, new IconTitleWidget(QIcon(), QString("Filesystem %1").arg(index)), w);
}

static void storeDataHelper(const QString& fname, const QByteArray& ba)
{
	QFile f(fname + QString(".dat"));
	if (f.open(QFile::WriteOnly))
	{
		f.write(ba);
		f.close();
	}
}

static QByteArray loadDataHelper(const QString& fname)
{
	QFile f(fname + QString(".dat"));
	if (f.open(QFile::ReadOnly))
	{
		QByteArray ba = f.readAll();
		f.close();
		return ba;
	}
	return QByteArray();
}

///////////////////////////////////////////////////////////////////////

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
//	ui->mainToolBar->hide();
	ui->statusBar->hide();
#if QT_VERSION >= 0x050000
	QObject::connect(ui->actionLayoutManager, &QAction::triggered, this, &MainWindow::showLayoutManager);
	QObject::connect(ui->actionAddSectionContent, &QAction::triggered, this, &MainWindow::onActionAddSectionContentTriggered);
#else
	QObject::connect(ui->actionLayoutManager, SIGNAL(triggered(bool)), this, SLOT(showLayoutManager()));
	QObject::connect(ui->actionAddSectionContent, SIGNAL(triggered(bool)), this, SLOT(onActionAddSectionContentTriggered()));
#endif

	_container = new ADS_NS::ContainerWidget();
	_container->setOrientation(Qt::Vertical);
	setCentralWidget(_container);

	// Test #1: Use high-level public API
	if (true)
	{
		ADS_NS::SectionWidget* sw1 = _container->addSectionContent(createLongTextLabelSC(_container));
		_container->addSectionContent(createCalendarSC(_container), sw1, ADS_NS::BottomDropArea);
		_container->addSectionContent(createFileSystemTreeSC(_container), NULL, ADS_NS::RightDropArea);
		_container->addSectionContent(createCalendarSC(_container));
//		_container->addSectionContent(createLongTextLabelSC(_container));
//		_container->addSectionContent(createLongTextLabelSC(_container));
//		_container->addSectionContent(createLongTextLabelSC(_container));
	}

	// Default window geometry
	resize(800, 600);

	// Restore window geometry and ContainerWidget state from last session
	restoreGeometry(loadDataHelper("MainWindow"));
	_container->restoreState(loadDataHelper("ContainerWidget"));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::showLayoutManager()
{
	LayoutManagerWidget* w = new LayoutManagerWidget(NULL);
	w->setAttribute(Qt::WA_DeleteOnClose, true);
	w->resize(500, 350);
	w->show();
}

void MainWindow::onActionAddSectionContentTriggered()
{
	return;
}

void MainWindow::contextMenuEvent(QContextMenuEvent* e)
{
	Q_UNUSED(e);
	QMenu* m = _container->createContextMenu();
	m->exec(QCursor::pos());
	delete m;
}

void MainWindow::closeEvent(QCloseEvent* e)
{
	Q_UNUSED(e);
	storeDataHelper("MainWindow", saveGeometry());
	storeDataHelper("ContainerWidget", _container->saveState());
}
