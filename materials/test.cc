
// создаем экземпляр QCustomPlot
QCustomPlot* plot = new QCustomPlot(this);

// устанавливаем флаг iRangeZoom для возможности масштабирования графика с помощью колесика мыши
plot->setInteraction(QCP::iRangeZoom, true);

// устанавливаем диапазон значений на оси x и y
plot->xAxis->setRange(-10, 10);
plot->yAxis->setRange(-5, 5);

// добавляем график функции y = sin(x)
QVector<double> x(101), y(101);
for (int i=0; i<101; ++i)
{
    x[i] = -M_PI + 2*M_PI*i/100.0;
    y[i] = qSin(x[i]);
}
plot->addGraph();
plot->graph(0)->setData(x, y);

// подписываемся на сигналы axisRangeChanged() и rescaleAxes() оси x и y
connect(plot->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onXAxisRangeChanged(QCPRange)));
connect(plot->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(onYAxisRangeChanged(QCPRange)));
connect(plot, SIGNAL(rescaleAxes()), this, SLOT(onRescaleAxes()));

// отображаем график
plot->replot();
