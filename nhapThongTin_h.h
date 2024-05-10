#ifndef STUDENT_H
#define STUDENT_H

struct SinhVien {
    char ten[100];
    char maSV[20];
    char email[30];
    char lop[100];
    double gpa;
    double canNang;
    char gioiTinh[5];
    double chieuCao;
    double BMI;
    char diaChi[30];
    char DOB[30];
};

typedef struct SinhVien SinhVien;

void taoMaSV(SinhVien *x);
void capEmail(SinhVien *x);
void Nhap(SinhVien *x, char *line);
void docThongTinTuFile(const char *tenTep, SinhVien a[], int *n);
void nhapThemThongTin(SinhVien* x);

#endif