#ifndef SPRING_VIEWER_H_
#define SPRING_VIEWER_H_

#include <QPaintEvent>
#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <cmath>

class Viewer : public QWidget {
	Q_OBJECT

	public:
		Viewer(QWidget* parent = nullptr) : QWidget(parent) {
			QTimer* timer = new QTimer(this);
    		connect(timer, SIGNAL(timeout()), this, SLOT(loop_slot()));
    		connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    		timer->start(1000.0f / 60.0f);
		}

	protected:
		void paintEvent(QPaintEvent* event) override {
    	QPainter painter(this);
   		painter.setRenderHint(QPainter::Antialiasing, true);
   		QPen pen(Qt::white, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    	painter.setPen(pen);
    	painter.setBrush({Qt::white, Qt::SolidPattern});
    	painter.drawRect(QRect(0, 0, width(), height()));

    	painter.setPen({Qt::red, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    	painter.drawPoint(QPointF{0.5f*width(), 0.5*height()});


    	painter.setPen({Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    	painter.drawPoint(QPointF{object_1_x + 0.5f*width(), object_1_y + 0.5*height()});

    	painter.setPen({Qt::black, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin});
    	painter.drawPoint(QPointF{object_2_x + 0.5f*width(), object_2_y + 0.5*height()});
}

	private slots:
		void loop_slot(){
			//float new_x = x + dt * v;
			//float new_v = v - dt * omega * omega * x;
			//x = new_x;
			//v = new_v;

			//v_x = v_x - dt * omega * omega * x;
			//v_y = v_y - dt * omega * omega * y;
			//x = x + dt * v_x;
			//y = y + dt * v_y;

			
			float norm_1 = ((object_1_x - object_2_x) * (object_1_x - object_2_x) + (object_1_y - object_2_y) * (object_1_y - object_2_y));
			norm_1 = norm_1 * std::sqrt(norm_1);
			//float norm_2 = ((object_2_x - object_1_x) * (object_2_x - object_1_x) + (object_2_y - object_1_y) * (object_2_y - object_1_y));
			//norm_2 = norm_2 * std::sqrt(norm_2);

			object_1_v_x = object_1_v_x + dt * omega * m2 * (object_2_x - object_1_x) / norm_1;
			object_1_v_y = object_1_v_y + dt * omega * m2 * (object_2_y - object_1_y) / norm_1;
			object_2_v_x = object_2_v_x + dt * omega * m1 * (object_1_x - object_2_x) / norm_1;
			object_2_v_y = object_2_v_y + dt * omega * m1 * (object_1_y - object_2_y) / norm_1;
			object_1_x = object_1_x + dt * object_1_v_x;
			object_1_y = object_1_y + dt * object_1_v_y;
			object_2_x = object_2_x + dt * object_2_v_x;
			object_2_y = object_2_y + dt * object_2_v_y;

		}

	private:
		float object_1_x{0.0f};
		float object_1_y{0.0f};
		float object_2_x{-100.0f};
		float object_2_y{0.0f};
		float object_1_v_x{0};
		float object_1_v_y{-3};
		float object_2_v_x{0};
		float object_2_v_y{300};
		float m1{1000.0f};
		float m2{10.0f};
		float dt{0.01f};
		float omega{10000.0f};
};


#endif // SPRING_VIEWER_H_