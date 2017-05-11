#ifndef __HW2__
#define __HW2__

#include "hw1.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
typedef unsigned int uint;
#include <iomanip>


template <typename T> class Image{
protected:
    int height;
    int width;
    

public:
    vector<T> local_buffer;
    Image(){}
    Image(int x, int y): height(y), width(x){}
    Image(vector<T> &copy_from, int x, int y)
     : height(y), width(x)
    {
      this->local_buffer = copy_from;
    }
    virtual ~Image(){}

    virtual void populate_image() = 0;
    virtual void print_image() = 0;
    virtual void average_image() = 0;
    virtual void invert_image() = 0;
    virtual T *index_image(int x_val, int y_val) = 0;
    virtual void replace_in_image(T *start, char color, T value) = 0;
    virtual void flip_image() = 0;
    virtual void copy_from(vector<T> &copy_from) = 0;
};


template <typename T> class CameraImage: public Image<T>{
public:
    CameraImage() : Image<T>(){}
    CameraImage(int x, int y) : Image<T>(x,y){}
    CameraImage(vector<T> &copy_from, int x, int y) : Image<T>(copy_from, x,y){}
    virtual ~CameraImage(){}

    virtual void populate_image(){
        hw::populate_vector(this->local_buffer);
    }

    virtual void print_image() {
        hw::print_vector(this->local_buffer, this->width, this->height);
    }

    virtual void average_image(){
        hw::average_vector(this->local_buffer);
    }

    virtual void invert_image(){
        hw::invert_vector(this->local_buffer);
    }

    virtual T *index_image(int x_val, int y_val){
        return hw::index_vector(this->local_buffer, this->width, this->height, x_val, y_val);
    }

    virtual void replace_in_image(T *start, char color, T value){
        hw::replace_in_vector(this->local_buffer, this->width, this->height, start, color, value);
    }

    virtual void flip_image(){
        hw::flip_vector(this->local_buffer, this->width, this->height);
    }

    //TODO copy from!
    void copy_from(vector<T> &copy_from){
      this->local_buffer = copy_from;

    }

    friend ostream &operator<<( ostream &output, 
         const CameraImage &img ){
      auto v = img.local_buffer;
      for (uint i = 0; i < v.size(); i++){
	if (i % (img.width * 3) == 0 && i != 0)
	  output << endl;
	output << setfill('0') << setw(3) << (int) v[i]  << " ";
	if (i % 3 == 2)
	  output << "\t";
      }
      return output;            
      }
    bool operator>(const CameraImage& img) {
      double lAve = 0;
      double rAve = 0;
      for (auto n: this->local_buffer){
	lAve += n;
      }
      for (auto n: img.local_buffer){
	rAve += n;
      }
      lAve /= (double) this->local_buffer.size();
      rAve /= (double) img.local_buffer.size();
      return lAve > rAve;
    }

    template <typename U> friend bool operator!=(const CameraImage<T>&left, const CameraImage<U>& img){
      const vector<T>& lhs = left.local_buffer;
      const vector<U>& rhs = img.local_buffer;
      if (lhs.size() != rhs.size())
	return true;
      
      for (uint i = 0; lhs.size(); i++){
	if (lhs[i] != (T) rhs[i]){
	  return true;
	}
      }
      return false;
    }
    //bool operator==(const CameraImage& lhs, const CameraImage& rhs) const{
    //  return lhs->local_buffer == rhs->local_buffer;
    // }
    template <typename U> friend bool operator==(const CameraImage<T>&left, const CameraImage<U>& img){
      //return this->local_buffer == img->local_buffer;
      //bool ans = true;
      //if (&left == (T*) &img)
      //	return true;
      const vector<T>& lhs = left.local_buffer;
      const vector<U>& rhs = img.local_buffer;
      if (lhs.size() != rhs.size())
	return false;
      
      for (uint i = 0; lhs.size(); i++){
	if (lhs[i] != (T) rhs[i]){
	  return false;
	}
      }
      return true;
    }

    
};

#endif
