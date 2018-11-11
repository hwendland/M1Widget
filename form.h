#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QPainter>
#include "../M1Kryptographie/nbild.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    void paintEvent(QPaintEvent *);
    void draw_image(QPaintEvent *, NBild image);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Form *ui;

   int img_width = 400;
   int img_height = 400;
   bool toogle_draw;

   NBild image;
};

#endif // FORM_H
