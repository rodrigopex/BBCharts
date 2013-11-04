// Default empty project template
#include "BBCharts.hpp"
#include <qdebug.h>

BBCharts::BBCharts(QObject * parent) :
		QObject(parent) {
	m_imageTracker = new ImageTracker;
	bool result = connect(m_imageTracker, SIGNAL(imageChanged(QVariant)), this,
			SIGNAL(imageChanged(QVariant)));
	Q_ASSERT(result);
	result = connect(m_imageTracker,
			SIGNAL(stateChanged(bb::cascades::ResourceState::Type)), this,
			SLOT(onStateChanged(bb::cascades::ResourceState::Type)));
	Q_ASSERT(result);
	Q_UNUSED(result);
	this->loadImage("zero_chart.amd");
}

bb::ImageData fromQImage(const QImage &qImage) {
	bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(),
			qImage.height());
	unsigned char *dstLine = imageData.pixels();
	for (int y = 0; y < imageData.height(); y++) {
		unsigned char * dst = dstLine;
		for (int x = 0; x < imageData.width(); x++) {
			QRgb srcPixel = qImage.pixel(x, y);
			*dst++ = qRed(srcPixel);
			*dst++ = qGreen(srcPixel);
			*dst++ = qBlue(srcPixel);
			*dst++ = qAlpha(srcPixel);
		}
		dstLine += imageData.bytesPerLine();
	}
	return imageData;
}

void BBCharts::onStateChanged(bb::cascades::ResourceState::Type state) {
	if (state == bb::cascades::ResourceState::Loaded) {
		qDebug() << "Trying to remove the generated file:" << m_currentFilePath;
		if(m_currentFilePath.startsWith("file:///"))
			QFile::remove(m_currentFilePath.replace("file://", ""));
	}
}

bb::cascades::Image BBCharts::image() const {
	return m_imageTracker->image();
}

void BBCharts::loadImage(const QString& imageSource) {
	m_currentFilePath = imageSource;
	m_imageTracker->setImageSource(QUrl(imageSource));
}

int graphY(int y, int height, int max) {
	return height * (1 - y / (double) max);
}

void BBCharts::drawChart() {
	int width = 720;
	int height = 300;
	int max = 5000;
	int step = width / 7;

	QImage tmp(QSize(width, height), QImage::Format_ARGB32_Premultiplied);
	QPainterPath path;

	int currentY = rand() % max;
	path.moveTo(0, graphY(currentY, height, max));
	for (int i = step; i < width; i += step) {
		currentY = rand() % max;
		qDebug() << currentY;
		path.lineTo(i, graphY(currentY, height, max));
	}

	QPainter ctx;
	ctx.begin(&tmp);
	ctx.setRenderHint(QPainter::Antialiasing);
	ctx.setPen(
			QPen(QColor("#00a8df"), 3, Qt::SolidLine, Qt::FlatCap,
					Qt::RoundJoin));
	ctx.drawPath(path);
	ctx.end();

	QString destinty = QDir::tempPath()
			+ QString("/chart%1.png").arg(rand() % 500);
	qDebug() << destinty;
	if (tmp.save(destinty, "PNG")) {
		qDebug() << "Image save successfully!";
		this->loadImage("file://" + destinty);
	}
}
