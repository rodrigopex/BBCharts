// Default empty project template
#include "BBCharts.hpp"
#include <qdebug.h>

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

Image BBCharts::image() const {
	return this->m_image;
}

void BBCharts::setImage(const QImage& img) {
	if (!img.isNull()) {
		Image tmp(fromQImage(img));
		m_image = tmp;
		emit this->imageChanged();
	}
}

void BBCharts::changePicture() {
	QPainterPath path;
	path.moveTo(0, 0);
	path.lineTo(30, 50);
	path.lineTo(40, 40);
	path.lineTo(50, 60);
	path.lineTo(70, 50);
	path.lineTo(90, 90);
	path.lineTo(100, 20);
	path.lineTo(110, 40);
	path.lineTo(120, 30);
	path.lineTo(130, 50);
	path.lineTo(140, 100);
	path.lineTo(150, 80);
	path.lineTo(180, 20);
	path.lineTo(200, 0);
	path.closeSubpath();
	path.setFillRule(Qt::WindingFill);
//	path.cubicTo(80, 0, 50, 50, 80, 80);

	QImage tmp(QSize(720, 720), QImage::Format_ARGB32_Premultiplied);
	tmp.fill(QColor("#00aa00"));
	QPainter ctx;
	ctx.beginNativePainting();
	ctx.begin(&tmp);
	ctx.scale(3.0, 3.0);
	ctx.setRenderHint(QPainter::Antialiasing);
	ctx.setPen(QPen(QColor("#555555"), 1,Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin));
	ctx.setBrush(QBrush(QColor(Qt::blue), Qt::SolidPattern));
//	ctx.drawRect(QRect(0, 0, 50, 50));
//	ctx.drawRect(QRect(30, 30, 50, 50));
	ctx.drawPath(path);
	ctx.rotate(180);
	ctx.end();
	this->setImage(tmp);

}

BBCharts::BBCharts(bb::cascades::Application *app) :
		QObject(app) {
	qRegisterMetaType<Image>("Image");
	QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_controller", this);
	AbstractPane *root = qml->createRootObject<AbstractPane>();
	app->setScene(root);
}

