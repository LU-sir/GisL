#pragma once

#include <qstring.h>
#include <qrect.h>
#include <qlist.h>
#include "GeoPoint.h"
#include "GeoPolyline.h"
#include "GeoPolygon.h"
#include "GeoObject.h"
#include "QUADTREE.h"

#define FLT_MAX         3.402823466e+38F
typedef struct quadtree_t QuadTree;

class CGeoLayer {
private:
    // ͼ����
    QString layerName;
    // �ɼ���
    bool isVisible;
    // ͼ�㷶Χ
    QRectF qRect;
    // ���Ա�ͷ
    QList<QString> propsKey;
public:
    CGeoLayer(void);

    virtual ~CGeoLayer(void);

    // ����Ŀ������
    QList<CGeoObject *> geoObjects;

    void setRect(QRectF qRect);

    QRectF getRect();

    bool showIndexGrid;

    void setLayerName(QString layerName);

    QString getLayerName();

    void setVisible(bool isVisible);

    bool getVisible();

    void setPropsKey();

    QList<QString> getPropsKey();

    void addObjects(CGeoObject *obj);

    void deleteObjectAt(int index);

    void deleteObjectAll();

    void paint(QPainter *paint);

    float *getVert(float *vert, int *count);

    QRectF getScope();

    bool paintLoc;
    int type; // 0:point 1:polyline 2:polygon
    QuadTree *tree;
    CGeoLayer *tessaLayer; // �ʷֽ��

};

