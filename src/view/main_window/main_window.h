#pragma once

#include "./ui_main_window.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QKeyEvent>

#include <facade.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace s21 {


class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(Facade &facade, QWidget *parent = nullptr);
        ~MainWindow();
    
    // public slots:
    //     void ICSData(Points *data);
    //     void IRawData(Points *data);

    private slots:
        void InterpolationHideButton();
        void InterpolationClearButton();
        void InterpolationFileButton();
        void CubicSplineButton();
        void NewtonPolynomialButton();
        void InterpolationGraphRemove(GraphName *name);
        void InterpolationCalcButton();

        void ApproximationHideButton();
        void ApproximationClearButton();
        void ApproximationFileButton();
        void ApproximateButton();
        void ApproximationGraphRemove(GraphName *name);
    
    protected:
        void keyPressEvent(QKeyEvent *event) override;

    // signals:
    //     void IClear();
    //     void IFile(QString file_name);
    //     void ICSPoints(int points);

    private:
        Ui::MainWindow *ui_;

        Facade &facade_;
        
        void InterpolationInit();
        void ApproximationInit();
        void InterpolationRawData(Points &data);
        void ApproximationRawData(Points &data);

        void InterpolationFileRead(const QString &filename);
        void ApproximationFileRead(const QString &filename);


        bool i_hide_{false};
        unsigned i_graphs_{0};
        QString i_filename_{};
        unsigned i_max_graphs_{5};

        bool a_hide_{false};
        unsigned a_graphs_{0};
        QString a_filename_{};
        unsigned a_max_graphs_{5};

        void InterpolationClearHelper();
        QString NameString(const QString &name, unsigned size);
        QString FileNameString(const QString &name, unsigned size);

        QString default_file_name_{"../materials/AAPL.csv"};
};

} // namespace s21
