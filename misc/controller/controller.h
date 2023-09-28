#pragma once

// #include <QObject>
#include "main_window.h"
#include "facade.h"

// #include "../common/data_struct.h"

namespace s21 {

class Controller final : private QObject {
    Q_OBJECT

    public:
        Controller(MainWindow &main_window, Facade &facade);
    // signals:
        // void InterpolationDone(Points points);
    
    // private slots:
    //     void StartInterpolation(std::string filename);
    

    private:
        MainWindow &view_;
        Facade &model_;


};



} // namespace s21
