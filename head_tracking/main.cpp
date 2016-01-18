#include "main_init.h"


int main(int argc, char** argv) {
	int flag = 0;
	KalmanFilter KF1(4, 2, 0);
	Mat_<float> state(4, 1);
	Mat_<float> processNoise(4, 1, CV_32F);
	Mat_<float> measurement1(2, 1);
	measurement1.setTo(Scalar(0));

	KF1.statePre.at<float>(0) = 0;
	KF1.statePre.at<float>(1) = 0;
	KF1.statePre.at<float>(2) = 0;
	KF1.statePre.at<float>(3) = 0;

	KF1.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1); // Including velocity
	KF1.processNoiseCov = (cv::Mat_<float>(4, 4) << 0.2, 0, 0.2, 0, 0, 0.2, 0, 0.2, 0, 0, 0.3, 0, 0, 0, 0, 0.3);

	setIdentity(KF1.measurementMatrix);
	setIdentity(KF1.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF1.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF1.errorCovPost, Scalar::all(.1));

	KalmanFilter KF2(4, 2, 0);
	//Mat_<float> state(4, 1);
	//Mat_<float> processNoise(4, 1, CV_32F);
	Mat_<float> measurement2(2, 1);
	measurement2.setTo(Scalar(0));

	KF2.statePre.at<float>(0) = 0;
	KF2.statePre.at<float>(1) = 0;
	KF2.statePre.at<float>(2) = 0;
	KF2.statePre.at<float>(3) = 0;

	KF2.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1); // Including velocity
	KF2.processNoiseCov = (cv::Mat_<float>(4, 4) << 0.2, 0, 0.2, 0, 0, 0.2, 0, 0.2, 0, 0, 0.3, 0, 0, 0, 0, 0.3);

	setIdentity(KF2.measurementMatrix);
	setIdentity(KF2.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF2.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF2.errorCovPost, Scalar::all(.1));

	KalmanFilter KF3(4, 2, 0);
	//Mat_<float> state(4, 1);
	//Mat_<float> processNoise(4, 1, CV_32F);
	Mat_<float> measurement3(2, 1);
	measurement3.setTo(Scalar(0));

	KF3.statePre.at<float>(0) = 0;
	KF3.statePre.at<float>(1) = 0;
	KF3.statePre.at<float>(2) = 0;
	KF3.statePre.at<float>(3) = 0;

	KF3.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1); // Including velocity
	KF3.processNoiseCov = (cv::Mat_<float>(4, 4) << 0.2, 0, 0.2, 0, 0, 0.2, 0, 0.2, 0, 0, 0.3, 0, 0, 0, 0, 0.3);

	setIdentity(KF3.measurementMatrix);
	setIdentity(KF3.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF3.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF3.errorCovPost, Scalar::all(.1));

	KalmanFilter KF4(4, 2, 0);
	//Mat_<float> state(4, 1);
	//	Mat_<float> processNoise(4, 1, CV_32F);
	Mat_<float> measurement4(2, 1);
	measurement4.setTo(Scalar(0));

	KF4.statePre.at<float>(0) = 0;
	KF4.statePre.at<float>(1) = 0;
	KF4.statePre.at<float>(2) = 0;
	KF4.statePre.at<float>(3) = 0;

	KF4.transitionMatrix = (Mat_<float>(4, 4) << 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1); // Including velocity
	KF4.processNoiseCov = (cv::Mat_<float>(4, 4) << 0.2, 0, 0.2, 0, 0, 0.2, 0, 0.2, 0, 0, 0.3, 0, 0, 0, 0, 0.3);

	setIdentity(KF4.measurementMatrix);
	setIdentity(KF4.processNoiseCov, Scalar::all(1e-4));
	setIdentity(KF4.measurementNoiseCov, Scalar::all(1e-1));
	setIdentity(KF4.errorCovPost, Scalar::all(.1));

	// *************************************************************** //
	// Mono Calibration                                                //
	// TODO                                                            //
	// *************************************************************** //

	//calibrateRealTime(0, boardSize, squareSize, cameraMatrix, distCoeffs,
	//		imagePoints, rvecs, tvecs,
	//		reprojErrs, totalAvgErr);

	cameraMatrix = (Mat_<float>(3, 3) << 889.651, 0, 319.5, 0, 889.651, 239.5, 0, 0, 1);
	distCoeffs = (Mat_<float>(5, 1) << -0.06471, 0.4719, 0, 0, -2.24498);//distCoeffs = (Mat_<float>(5, 1) << -0.60553, 28.6678, 0, 0, -316.316);

	cout << "camera matrix:" << cameraMatrix << endl;
	cout << "distort coefficient:" << distCoeffs << endl;


	// *************************************************************** //
	// Marker Detection                                                //
	// *************************************************************** //

	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened()){  // check if we succeeded
		cout << "ERROR: camera cannot be loaded." << endl;
		//return -1;
	}

	vector<vector<Point> > squares;
	vector<vector<Point2f> > squares_2f;
	vector<Point2f> marker;
	vector<Point2f> marker_filter;
	Mat prev_frame;
	int first = 1;
	while (true)
	{
		// retrieve the frame:
		Mat frame, output;
		if (!cap.read(frame)) {
			std::cout << "Unable to retrieve frame from video stream." << std::endl;
			continue;
		}
		// display it:
		//imshow("LiveStream", frame);




		// ************ //
		// thresholding //
		// ************ //
		Mat gray_frame, threshframe;
		cvtColor(frame, gray_frame, COLOR_BGR2GRAY);
		Mat diff_frame;
		threshold(gray_frame, threshframe, thresh, 255, THRESH_BINARY_INV);
		medianBlur(threshframe, threshframe, 5);
		imshow("threshold", threshframe);


		//if (first){

		//	threshold(gray_frame, threshframe, thresh, 255, THRESH_BINARY_INV);
		//	medianBlur(threshframe, threshframe, 5);
		//	imshow("threshold", threshframe);
		//	first = 0;
		//	prev_frame = gray_frame;
		//}
		//else{

		//	absdiff(gray_frame, prev_frame, diff_frame);
		//	threshold(diff_frame, threshframe, thresh, 255, THRESH_BINARY_INV);
		//	medianBlur(threshframe, threshframe, 5);
		//	imshow("threshold", threshframe);

		//}

		
		// *************************************************************** //
		// Using Sqaure Detection                                          //
		// *************************************************************** //
		vector<vector<Point> > contours;
		findContours(threshframe, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);


		vector<Point2f> approx_2f;
		vector<Point> approx;

		squares.clear();
		squares_2f.clear();
		//marker.clear();

		// test each contour
		for (size_t i = 0; i < contours.size(); i++)
		{

			approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);
			approxPolyDP(Mat(contours[i]), approx_2f, arcLength(Mat(contours[i]), true)*0.02, true);


			if (approx.size() == 4 &&
				fabs(contourArea(Mat(approx))) > 100 &&//1000 &&
				isContourConvex(Mat(approx)))
			{
				squares.push_back(approx);
				squares_2f.push_back(approx_2f);

			}
		}


		for (int i = 0; i < squares_2f.size(); i++){
			// ***************************** //
			// extracting region of interest //
			// ***************************** //		

			vector<Point2f> perspective_pt = marekr_image_pt();
			Mat canonicalMarker;
			Mat M = getPerspectiveTransform(squares_2f[i], perspective_pt);
			warpPerspective(gray_frame, canonicalMarker, M, Size(frame.cols, frame.rows));

			threshold(canonicalMarker, canonicalMarker, 125, 255, THRESH_BINARY | THRESH_OTSU);
			Rect myROI(0, 0, 270, 270);
			Mat croppedImage = canonicalMarker(myROI);
			//imshow("cropped", croppedImage); 
			//imshow("perspective", canonicalMarker);

			// *************** //
			// validate marker //
			// *************** //
			Rect subsqr(0, 0, 30, 30);
			Mat subView = croppedImage(subsqr);
			Mat bitMatrix = Mat::zeros(9, 9, CV_8UC1);
			int cellSize = 30;

			for (int y = 0; y < 9; y++)
			{
				for (int x = 0; x<9; x++)
				{
					int cellX = (x)*cellSize;
					int cellY = (y)*cellSize;
					Mat cell = croppedImage(Rect(cellX, cellY, cellSize, cellSize));
					int nZ = cv::countNonZero(cell);
					if (nZ>(cellSize*cellSize) / 2){
						bitMatrix.at<uchar>(y, x) = 1;
					}
				}
			}

			Mat diff;
			Mat rotmarker;

			for (int a = -2; a < 2; a++){
				Mat refmarker;
				Mat markerMatrix = (Mat_<int>(9, 9) <<
					0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 1, 1, 0, 0, 0, 0, 0,
					0, 0, 1, 1, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0,
					0, 0, 0, 0, 0, 0, 0, 0, 0);
				markerMatrix.convertTo(refmarker, CV_8UC1);

				//cout << "bitmap\n" << bitMatrix << endl;
				if (a == -2){
					rotmarker = refmarker;
					//cout << "rotation\n" << rotmarker << endl;
				}
				else{
					flip(refmarker, rotmarker, a);
					// -1: both axis
					//  0: x-axis
					//  1: y-axis
					//cout << "rotation\n" << rotmarker << endl;
				}
				compare(bitMatrix, rotmarker, diff, CMP_EQ);

				bool eq = cv::countNonZero(diff) == 81;

				if (eq){
					marker.clear();
					//cornerSubPix(threshframe, squares_2f[i], Size(11, 11), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));
					if (a == -1){
						//cout << "orientation: reflected to both axis" << endl;
						for (int b = 0; b < 4; b++){
							marker.push_back(squares_2f[i][(b + 2) % 4]);
						}
					}
					else if (a == 0){
						//cout << "orientation: reflected to x-axis" << endl;
						for (int b = 0; b < 4; b++){
							marker.push_back(squares_2f[i][(b + 1) % 4]);
						}
					}
					else if (a == 1){
						//cout << "orientation: reflected to y-axis" << endl;
						for (int b = 0; b < 4; b++){
							marker.push_back(squares_2f[i][(b + 3) % 4]);
						}
					}
					else if (a == -2){
						//cout << "orientation: no reflection" << endl;
						for (int b = 0; b < 4; b++){
							marker.push_back(squares_2f[i][(b) % 4]);
						}
					}
					else{
						cout << "ERROR" << endl;
					}
					squareindex = i;
					//drawMarker(frame, squares, squareindex);
					//cout << "marker detected" << endl;
					flag = 1;
					break;

				}
			}
		}
		//	drawSquares(frame, squares);


		if (flag){
			marker_filter.clear();

			for (int c = 0; c < marker.size(); c++){

				if (c == 0){
					Mat prediction = KF1.predict();
					Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

					drawCross(frame, marker[c], Scalar(255, 0, 0), 5);
					measurement1(0) = marker[c].x;
					measurement1(1) = marker[c].y;
					Point measPt(measurement1(0), measurement1(1));

					Mat estimated = KF1.correct(measurement1);
					Point statePt(estimated.at<float>(0), estimated.at<float>(1));
					marker_filter.push_back(statePt);

					drawCross(frame, statePt, Scalar(255, 255, 255), 5);

				}
				else if (c == 1){

					Mat prediction = KF2.predict();
					Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

					drawCross(frame, marker[c], Scalar(255, 0, 0), 5);
					measurement2(0) = marker[c].x;
					measurement2(1) = marker[c].y;
					Point measPt(measurement2(0), measurement2(1));

					Mat estimated = KF2.correct(measurement2);
					Point statePt(estimated.at<float>(0), estimated.at<float>(1));
					marker_filter.push_back(statePt);

					drawCross(frame, statePt, Scalar(255, 255, 255), 5);

				}
				else if (c == 2){

					Mat prediction = KF3.predict();
					Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

					drawCross(frame, marker[c], Scalar(255, 0, 0), 5);
					measurement3(0) = marker[c].x;
					measurement3(1) = marker[c].y;
					Point measPt(measurement3(0), measurement3(1));

					Mat estimated = KF3.correct(measurement3);
					Point statePt(estimated.at<float>(0), estimated.at<float>(1));
					marker_filter.push_back(statePt);

					drawCross(frame, statePt, Scalar(255, 255, 255), 5);

				}
				else if (c == 3){

					Mat prediction = KF4.predict();
					Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

					drawCross(frame, marker[c], Scalar(255, 0, 0), 5);
					measurement4(0) = marker[c].x;
					measurement4(1) = marker[c].y;
					Point measPt(measurement4(0), measurement4(1));

					Mat estimated = KF4.correct(measurement4);
					Point statePt(estimated.at<float>(0), estimated.at<float>(1));

					drawCross(frame, statePt, Scalar(255, 255, 255), 5);
					marker_filter.push_back(statePt);


				}


			}
			imshow("trakcing", frame);
			//cornerSubPix(threshframe, marker_filter, Size(5, 5), Size(-1, -1), TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 30, 0.1));

		}


		// *************************************************************** //
		// Pose Estimation                                                 //
		// *************************************************************** //
		vector<Point3f> world_pt = marker_world_pt();	// 3d world coordinates
		vector<Point3f> cube_pt = cube_3d();	//3d cub

		Mat R_move, T_move;


		if (marker_filter.size() != 0){
			vector<Point2f> cube_2d;
			solvePnPRansac(world_pt, marker_filter, cameraMatrix, distCoeffs, R_move, T_move,false , 300, 0.01);
			cout << "rotation matrix: " << R_move << endl;
			cout << "translation matrix: " << T_move << endl;

			projectPoints(cube_pt, R_move, T_move, cameraMatrix, distCoeffs, cube_2d);

			//drawCorner(frame, marker_filter, radius);

			drawCube(frame, cube_2d);
		}


		if (marker.size() != 0){
			vector<Point2f> cube_2d;
			solvePnPRansac(world_pt, marker, cameraMatrix, distCoeffs, R_move, T_move);
			cout << "rotation matrix: " << R_move << endl;
			cout << "translation matrix: " << T_move << endl;

			projectPoints(cube_pt, R_move, T_move, cameraMatrix, distCoeffs, cube_2d);

			drawCorner(frame, marker, radius);

			drawCube(frame, cube_2d);
		}
		
		if (waitKey(30) == 27)
			break;

	}




	cap.release();
	return 0;
}



