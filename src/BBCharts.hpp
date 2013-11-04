// Default empty project template
#ifndef BBCharts_HPP_
#define BBCharts_HPP_

#include <QObject>
#include <QtCore>
#include <bb/cascades/Image>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>
#include <bb/cascades/ImageView>
#include <bb/cascades/ResourceState>
#include <bb/cascades/ImageTracker>


#include <bb/ImageData>
#include <Qt/qimage.h>

using namespace bb::cascades;

/*!
 * @brief Application pane object
 *
 *Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class BBCharts : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bb::cascades::Image image READ image NOTIFY imageChanged);

public:
    BBCharts(QObject * parent = 0);
    virtual ~BBCharts() {}
    bb::cascades::Image image() const;
    void loadImage(const QString& imageSource);
    Q_INVOKABLE void drawChart();
Q_SIGNALS:
    void imageChanged(QVariant image);
private slots:
	void onStateChanged(bb::cascades::ResourceState::Type type);
private:
    bb::cascades::ImageTracker * m_imageTracker;
    QString m_currentFilePath;
};


#endif /* BBCharts_HPP_ */
