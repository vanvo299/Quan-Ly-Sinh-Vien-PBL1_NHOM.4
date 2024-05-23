#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

#include "giaoDien_h.h"
#include "nhapThongTin_h.h"
#include "sapXepThongTin_h.h"
#include "timKiemVaXoa_h.h"
#include "xuatThongTin_h.h"
#include "xuLyThongTin_h.h"


void gotoxy(int x,int y);
void taoMaSV(SinhVien *x);
void capEmail(SinhVien *x);
void docThongTinTuFile(const char *tenTep, SinhVien a[], int *n);
void nhapThemThongTin(SinhVien* x);
int soSanhTenSinhVien(SinhVien *sv1, SinhVien *sv2);
void sapXepTheoTen(SinhVien a[], int n);
void sapXepTheoGPA(SinhVien a[], int n);
void in(SinhVien *x, int n);
void timKiemTheoTen(SinhVien a[], int n, char name[]);
void timKiemTheoMaSV(SinhVien a[], int n, char ID[]);
void xoaThongTin(SinhVien a[], int* n, char ID[]);
void in(SinhVien *x, int n);
void inSucKhoe(SinhVien *x, int n);
void xuatFile(SinhVien *x, int n);

int main() {
    int max_students = 1000;
    SinhVien *a = (SinhVien*)malloc(sizeof(SinhVien) * max_students);
    int n = 0;
    char pass[20] = "pbl1\0";
    char pa[20];
    system("color f0");
    gotoxy(53, 9);
    printf("DANG NHAP(NHAN ENTER SAU KHI NHAP MAT KHAU)");
    gotoxy(55, 10);
    printf("____________________________________");
    gotoxy(55, 11);
    printf("|                                  |");
    gotoxy(55, 12);
    printf("|__________________________________|");
    gotoxy(70, 11);
    gets(pa);

    if (strcmp(pass, pa) == 0) {
        system("cls");

        while (1) {
            printf("\n\t    --DO AN LAP TRINH TINH TOAN--\t\t\t\n");
            printf("THUC HIEN BOI: LUONG VAN VO & NGUYEN DANG BAO NGUYEN\n\n");
            printf("1. 23T_DT1 \n");
            printf("2. 23T_DT2 \n");
            printf("0. Thoat \n");
            printf("VUI LONG CHON LOP: ");
            int lc_class;
            scanf("%d", &lc_class);

            switch (lc_class) {
                case 1:
                    docThongTinTuFile("23T_DT1.txt", a, &n);
                    break;
                case 2:
                    n = 0;
                    docThongTinTuFile("23T_DT2.txt", a, &n);
                    for (int i = 0; i < n; i++) {
                        strcpy(a[i].maSV, "");
                        strcpy(a[i].email, "");
                    }
                    break;
                case 0:
                    free(a);
                    return 0;
                default:
                    printf("Lua chon khong hop le, vui long chon lai.\n");
                    continue;
            }

            while (1) {
                printf("\nTRUONG DAI HOC BACH KHOA - DAI HOC DA NANG\n");
                printf("         KHOA CONG NGHE THONG TIN\n");
                printf("-----------------------------------------------\n");
                printf("PBL1: DO AN LAP TRINH TINH TOAN\t\t\t\n");
                printf("DE TAI: QUAN LY DANH SACH SINH VIEN\n");
                printf("GIANG VIEN HUONG DAN: NGUYEN CONG DANH\n");
                printf("SINH VIEN THUC HIEN: - LUONG VAN VO \n");
                printf("                     - NGUYEN DANG BAO NGUYEN\n\n");
                printf("-----QUAN LY DANH SACH SINH VIEN-------\n");
                printf("1. Cap ma sinh vien\n");
                printf("2. Cap email sinh vien\n");
                printf("3. Tim kiem sinh vien\n");
                printf("4. Xoa sinh vien theo ma sinh vien\n");
                printf("5. Sap xep sinh vien\n");
                printf("6. Hien thi danh sach sinh vien\n");
                printf("7. Nhap them thong tin sinh vien\n");
                printf("8. Xuat file danh sach sinh vien\n");
                printf("0. Thoat !                      \n");
                printf("---------------------------------------\n\n");
                printf("Nhap lua chon: ");
                int lc;
                scanf("%d", &lc);

                switch (lc) {
                    case 1: {
                        int temp = 0;
                        for (int i = 0; i < n; i++) {
                            for (int j = i + 1; j < n; j++) {
                                if (soSanhTenSinhVien(&a[i], &a[j]) > 0) {
                                    temp = 1;
                                }
                            }
                        }
                        if (temp == 0) {
                            printf("Da cap ma sinh vien\n");
                            for (int i = 0; i < n; i++) {
                                taoMaSV(&a[i]);
                            }
                        } else {
                            printf("Vui long sap xep sinh vien theo thu tu tu A - Z truoc khi cap ma !!!\n");
                        }
                        break;
                    }
                    case 2: {
                        int temp = 0;
                        for (int i = 0; i < n; i++) {
                            if (strlen(a[i].maSV) == 0) {
                                printf("Ma sinh vien chua duoc cap, vui long cap ma sinh vien truoc khi cap email\n");
                                temp = 1;
                                break;
                            }
                        }
                        if (temp == 0) {
                            for (int i = 0; i < n; i++) {
                                capEmail(&a[i]);
                            }
                            printf("Da cap email sinh vien\n");
                        }
                        break;
                    }
                    case 3: {
                        int choice;
                        printf("1. Tim kiem sinh vien theo ten sinh vien\n");
                        printf("2. Tim Kiem sinh vien theo ma sinh vien\n\n");
                        printf("Vui long chon lua chon cua ban: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1: {
                                int temp = 0;
                                for (int i = 0; i < n; i++) {
                                    if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                        printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi tim kiem\n");
                                        temp = 1;
                                        break;
                                    }
                                }
                                if (temp == 0) {
                                    char name[100];
                                    printf("Nhap ten sinh vien can tim kiem: ");
                                    getchar();
                                    gets(name);
                                    timKiemTheoTen(a, n, name);
                                }
                                break;
                            }
                            case 2: {
                                int temp = 0;
                                for (int i = 0; i < n; i++) {
                                    if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                        printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi tim kiem\n");
                                        temp = 1;
                                        break;
                                    }
                                }
                                if (temp == 0) {
                                    printf("Nhap ma cua sinh vien can tim kiem: ");
                                    char ID[20];
                                    getchar();
                                    gets(ID);
                                    timKiemTheoMaSV(a, n, ID);
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case 4: {
                        int temp = 0;
                        for (int i = 0; i < n; i++) {
                            if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xoa\n");
                                temp = 1;
                                break;
                            }
                        }
                        if (temp == 0) {
                            char ID[20];
                            printf("Nhap ma sinh vien can xoa: ");
                            getchar();
                            gets(ID);
                            xoaThongTin(a, &n, ID);
                        }
                        break;
                    }
                    case 5: {
                        int choice;
                        printf("1. Sap xep sinh vien co GPA giam dan\n");
                        printf("2. Sap xep sinh vien theo ten (tu a - z)\n\n");
                        printf("Vui long chon lua chon cua ban: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1: {
                                int temp = 0;
                                for (int i = 0; i < n; i++) {
                                    if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                        printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi sap xep\n");
                                        temp = 1;
                                        break;
                                    }
                                }
                                if (temp == 0) {
                                    sapXepTheoGPA(a, n);
                                }
                                break;
                            }
                            case 2:
                                sapXepTheoTen(a, n);
                                printf("Da sap xep danh sach sinh vien theo thu tu tu A - Z. \n");
                                break;
                        }
                        break;
                    }
                    case 6: {
                        int choice;
                        printf("1. Danh sach thong tin sinh vien\n");
                        printf("2. Danh sach suc khoe sinh vien\n\n");
                        printf("Vui long chon lua chon cua ban: ");
                        scanf("%d", &choice);

                        switch (choice) {
                            case 1: {
                                int temp = 0;
                                for (int i = 0; i < n; i++) {
                                    if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                        printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
                                        temp = 1;
                                        break;
                                    }
                                }
                                if (temp == 0) {
                                    printf("\t\t\t DANH SACH SINH VIEN\t\t\t\n");
                                    printf("STT\tHO VA TEN\t        MA SINH VIEN\tEMAIL\t                        GIOI TINH\tLOP\t        GPA\tNGAY THANG NAM SINH \t DIA CHI\n");
                                    for (int i = 0; i < n; i++) {
                                        printf("%d", i + 1);
                                        in(&a[i], n);
                                    }
                                }
                                break;
                            }
                            case 2: {
                                int temp = 0;
                                for (int i = 0; i < n; i++) {
                                    if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                        printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
                                        temp = 1;
                                        break;
                                    }
                                }
                                if (temp == 0) {
                                    printf("\t\tTHONG TIN SUC KHOE SINH VIEN\t\t\t\n");
                                    printf("STT\tHO VA TEN\t        MA SINH VIEN\tGIOI TINH\tLOP\t    NGAY THANG NAM SINH\t   CHIEU CAO\t CAN NANG \t BMI\n");
                                    for (int i = 0; i < n; i++) {
                                        printf("%d", i + 1);
                                        inSucKhoe(&a[i], n);
                                    }
                                }
                                break;
                            }
                        }
                        break;
                    }
                    case 7: {
                        int temp = 0;
                        for (int i = 0; i < n; i++) {
                            if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
                                temp = 1;
                                break;
                            }
                        }
                        if (temp == 0) {
                            SinhVien newStudent;
                            printf("Nhap vao thong tin cua sinh vien \n");
                            int soLuongSvCanThem;
                            printf("Nhap so luong sinh vien can them: ");
                            scanf("%d", &soLuongSvCanThem);
                            printf("\n");
                            for (int i = 0; i < soLuongSvCanThem; i++) {
                                printf("Thong tin sinh vien thu %d\n", i + 1);
                                nhapThemThongTin(&newStudent);
                                a[n++] = newStudent;
                                printf("\n");
                            }
                            printf("\nDa them %d sinh vien vao lop.\n", soLuongSvCanThem);
                        }
                        break;
                    }
                    case 8: {
                        int temp = 0;
                        for (int i = 0; i < n; i++) {
                            if ((strlen(a[i].maSV) == 0) || (strlen(a[i].email)) == 0) {
                                printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
                                temp = 1;
                                break;
                            }
                        }
                        if (temp == 0) {
                            xuatFile(a, n);
                        }
                        break;
                    }
                    case 0:
                        free(a);
                        return 0;
                    default:
                        printf("Nhap khong hop le, vui long nhap lai!!!\n");
                        break;
                }
            }
        }
    } else {
        printf("\n\n\t\t\t\t\t\t\tVUI LONG KIEM TRA LAI MAT KHAU!");
    }

    free(a);
    return 0;
}