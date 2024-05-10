#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>


#include "xuatThongTin_h.h"

void in(SinhVien *x, int n)
{
    printf("\t%-22s\t%-5s\t%-30s\t%-10s\t%-10s\t%.2lf\t%s\t         %-20s\n", x->ten,x->maSV,x->email, x->gioiTinh, x->lop, x->gpa, x->DOB, x->diaChi);   
}

// ham in thong tin suc khoe sinh vien
void inSucKhoe(SinhVien *x, int n)
{
    tinh_BMI(x);
    printf("\t%-22s\t%-5s\t%-10s\t%-10s  %s\t           %.2lf cm\t %.2lf kg\t %.2lf\n", x->ten,x->maSV, x->gioiTinh, x->lop, x->DOB, x->chieuCao, x->canNang, x->BMI);
}

void xuatFile(SinhVien *x, int n) {
    for (int i = 0; i < n; i++) {
        if ((strlen(x[i].maSV) == 0) || (strlen(x[i].email) == 0)) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien truoc khi xuat danh sach\n");
            return;
        }
    }
    printf("Da xuat danh sach sinh vien ra file\n");
    FILE *outputFile = fopen("danhSachSinhVien.txt", "w");
    if (outputFile) {
        fprintf(outputFile, "\t\t\t DANH SACH SINH VIEN \t\t\n");
        fprintf(outputFile, "STT\tHO VA TEN\t        MA SINH VIEN\tEMAIL\t                        GIOI TINH\tLOP\t        GPA\tNGAY THANG NAM SINH \t DIA CHI\n");

        for (int i = 0; i < n; i++) {
            tinh_BMI(&x[i]);
            fprintf(outputFile, "%-3d\t%-22s\t%-5s\t%-30s\t%-10s\t%-10s\t%.2lf\t%s\t %17s\n",
                                i + 1, x[i].ten, x[i].maSV, x[i].email, x[i].gioiTinh, x[i].lop, x[i].gpa, x[i].DOB, x[i].diaChi);
        }
        fclose(outputFile);
    }
}

