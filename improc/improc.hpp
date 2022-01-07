#include "bitmap.c"
#define ARRAY_2D 1
#define VECTOR_OF_VECTORS 2
#ifndef MATRIX_DATA_TYPE
 #define MATRIX_DATA_TYPE ARRAY_2D  //if not defined, we define it as a 2d matrix by default
#endif

#if MATRIX_DATA_TYPE == ARRAY_2D
	//2d matrix
	template<class T>
	class MatrixData{
		public:
			int r, c;
			T** matrix;
			MatrixData(){
			}
			MatrixData(int r, int c){  //allocating memory to the the matrix(2d array)
				this->r = r;
				this->c = c;
				matrix = new T*[r];
				for(int x = 0; x < r; x++){
					matrix[x] = new T[c];
				}
			}
			MatrixData(MatrixData<T>& mdata){
				this->r = mdata->r;
				this->c = mdata->c;
				matrix = new T*[r];
				for(int x = 0; x < r; x++){
					matrix[x] = new T[c];
					for(int y = 0; y < c; y++){
						matrix[x][y] = mdata->matrix[x][y];
					}
				}
			}
			MatrixData<T>& operator=(MatrixData<T>& mdata){
				this->r = mdata.r;
				this->c = mdata.c;
				matrix = new T*[r];
				for(int x = 0; x < r; x++){
					matrix[x] = new T[c];
					for(int y = 0; y < c; y++){
						matrix[x][y] = mdata.matrix[x][y];
					}
				}
				return *this;
			}
			void initialize(T v){
				for(int x = 0; x < r; x++){
					for(int y = 0; y < c; y++){
						matrix[x][y] = v;
					}
				}
			}
	};
#elif MATRIX_DATA_TYPE == VECTOR_OF_VECTORS
	//vector of vectors
	template<class T>
	class MatrixData{
		int r, c;
		public:
		vector<vector<T> > matrix;
		MatrixData(){
			
		}
		MatrixData(int r, int c){   //allocating memory to the the matrix(vector of vectors)
			this->r = r;
			this->c = c;
			for(int x = 0; x < r; x++){
				vector<T> hold;
				for(int y = 0; y < c; y++){
					hold.push_back(0);
				}
				matrix.push_back(hold);
			}
		}
		MatrixData(MatrixData<T>* mdata){
			this->r = mdata->r;
			this->c = mdata->c;
			for(int x = 0; x < r; x++){
				vector<T> hold;
				for(int y = 0; y < c; y++){
					hold.push_back(0);
				}
				matrix.push_back(hold);
			}
		}
		void initialize(T v){
			for(int x = 0; x < r; x++){
				for(int y = 0; y < c; y++){
					matrix[x][y] = v;
				}
			}
		}
		void show(){
			for(int x = 0; x < r; x++){
				for(int y = 0; y < c; y++){
					std::cout << matrix[x][y] << " ";
				}
				std::cout << std::endl;
			}
		}
	};
#endif

template<class T>
class Matrix{
	public:
		int r, c;
		MatrixData<T>* matrixdata;
		Matrix(){
		}
		Matrix(int r, int c, T v){
			this->r = r;
			this->c = c;
			matrixdata = new MatrixData<T>(r, c);
			matrixdata->initialize(v);
		}
		Matrix(Matrix<T>* matrix){
			this->r = matrix->r;
			this->c - matrix->c;
			matrixdata = new MatrixData<T>;
			matrixdata = matrix->matrixdata;
		}
		Matrix<T>& operator=(Matrix<T>& matrix){
			*matrixdata = *(matrix.matrixdata);
			return *this;
		}
		int get_nrows(){
			return r;
		}
		int get_ncols(){
			return c;
		}
		~Matrix() {
			for(int i = 0; i < r; ++i) {
		        delete[] matrixdata->matrix[i];   
		    }
		    delete[] matrixdata->matrix;
		}
};

template<class T>
class Image{   //the basic image class
	public:
		Matrix<T>* matrix;
		int h, w;
		BITMAPFILEHEADER header;
		BITMAPINFO* bmp_info;
		Image(){
			matrix = new Matrix<T>;
			bmp_info = NULL;
		}
		Image(int h, int w, BITMAPINFO* bmi, BITMAPFILEHEADER hdr){
			this->h = h;
			this->w = w;
			matrix = new Matrix<T>(h, w, 0);
			header = hdr;
			bmp_info = bmi;
		}
		Image(int h, int w, BITMAPINFO* bmi, BITMAPFILEHEADER hdr, int data){
			this->h = h;
			this->w = w;
			matrix = new Matrix<T>(h, w, data);
			header = hdr;
			bmp_info = bmi;
		}
		Image(Image& image){
			this->h = image.h;
			this->w = image.w;
			header = image.header;
			bmp_info = image.bmp_info;
			matrix = new Matrix<T>(image.matrix);   //to avoid pointers of this object and the passed object to point at the same address
		}
		Image& operator=(Image& image){
			this->h = image.h;
			this->w = image.w;
			header = image.header;
			bmp_info = image.bmp_info;
			matrix = new Matrix<T>(h, w, 0);
			*matrix = *(image.matrix); 
			return *this;
		}
		const BITMAPFILEHEADER& get_bitmapheader(){
			return header;
		}
		BITMAPINFO* get_bitmapinfo(){
			return bmp_info;
		}
		
		void setBmpInfo(BITMAPINFO* bmp_info){
			this->bmp_info = bmp_info;
		}
};
