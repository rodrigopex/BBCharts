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

    Q_PROPERTY(Image image READ image NOTIFY imageChanged);

public:
    BBCharts(Application *app);
    virtual ~BBCharts() {}
    Image image() const;
    void setImage(const QImage& img);
    Q_INVOKABLE void changePicture();
Q_SIGNALS:
    void imageChanged();
private:
    Image m_image;
};


#endif /* BBCharts_HPP_ */
