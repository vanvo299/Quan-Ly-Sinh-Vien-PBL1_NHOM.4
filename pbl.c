/*
DỰ ÁN PBL1: LẬP TRÌNH TÍNH TOÁN
Chủ đề: Xây dựng chương trình quản lý sinh viên
Nhóm: 
Người thực hiện: Lương Văn Võ & Nguyễn Đặng Bảo Nguyên
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>

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

// ham cap ma sinh vien 
void taoMaSV(SinhVien *x) {
    static int counter = 1; 
    sprintf(x->maSV, "102230%03d", counter);
    counter++; 
}

// ham cap email cho sinh vien
void capEmail(SinhVien *x) 
{
    sprintf(x->email, "%s@sv1.dut.udn.vn", x->maSV);
}

// Nhap thong tin sinh vien va tra ve sinh vien sau khi nhap
void Nhap(SinhVien* x, char* line) {
    char* token = strtok(line, "|");
    if (token != NULL)
        strcpy(x->ten, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->gioiTinh, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->lop, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        x->gpa = atof(token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->diaChi, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        strcpy(x->DOB, token);

    token = strtok(NULL, "|");
    if (token != NULL)
        x->canNang = atof(token);

    token = strtok(NULL, "|");
    if (token != NULL)
        x->chieuCao = atof(token);
}

// ham tinh BMI
void tinh_BMI(SinhVien *x) { 
    double chieuCao_meters = x->chieuCao / 100.0;
    x->BMI = x->canNang / pow(chieuCao_meters, 2);
}

// ham in thong tin sinh vien
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

//ham sap xep theo ten
// Hàm để tách phần họ và tên từ chuỗi hoTen và lưu vào mảng ten
void tachHoTen(char hoTen[], char ten[]) {
    // Tìm vị trí khoảng trắng cuối cùng trong họ tên
    char *viTriKhoangTrangCuoi = strrchr(hoTen, ' ');
    if (viTriKhoangTrangCuoi != NULL) {
        strcpy(ten, viTriKhoangTrangCuoi + 1);
    } else {
        strcpy(ten, hoTen);
    }
}

// Hàm so sánh tên của hai sinh viên
int soSanhTenSinhVien(SinhVien *sv1, SinhVien *sv2) {
    char tenSV1[100], tenSV2[100];
    tachHoTen(sv1->ten, tenSV1);
    tachHoTen(sv2->ten, tenSV2);
    return strcasecmp(tenSV1, tenSV2);
}

// Hàm đổi chỗ giữa hai sinh viên
void swapSinhVien(SinhVien *a, SinhVien *b) {
    struct SinhVien temp = *a;
    *a = *b;
    *b = temp;
}

// Hàm chia mảng theo pivot
int Pivot(SinhVien a[], int low, int high) {
    SinhVien pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (soSanhTenSinhVien(&a[j], &pivot) <= 0) {
            i++;
            swapSinhVien(&a[i], &a[j]);
        }
    }

    swapSinhVien(&a[i + 1], &a[high]);
    return i + 1;
}

// Hàm sắp xếp Quick Sort
void quickSort(SinhVien a[], int low, int high) {
    if (low < high) {
        int pivot = Pivot(a, low, high);

        quickSort(a, low, pivot - 1);
        quickSort(a, pivot + 1, high);
    }
}

// Hàm sắp xếp sinh viên theo tên bằng Quick Sort
void sapXepTheoTen(SinhVien a[], int n) {
    quickSort(a, 0, n - 1);
}

// xuat danh sach sinh vien ra file   
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

// ham de chuyen xau tat ca thanh chu thuong (VD: HELLO -> hello)
void toLowerCase(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = tolower(str[i]); // Chuyển đổi ký tự thành chữ thường
        i++;
    }
}

// tim kiem theo ten
void timKiemTheoTen(SinhVien a[], int n, char name[]) {
    int find = 0;
        char tmpTen[50];
        strcpy(tmpTen, name);
        toLowerCase(tmpTen);
        
    for (int i = 0; i < n; i++) {
        char tmpName[50];
        strcpy(tmpName, a[i].ten);
        toLowerCase(tmpName);
        // Su dung strstr de kiem tra tên có xuat hien trong tên sinh viên không
        if (strstr(tmpName, tmpTen) != NULL) {
            if (!find) {
                printf("STT\tHO VA TEN\t        MA SINH VIEN\tEMAIL\t                        GIOI TINH\tLOP\t        GPA\tNGAY THANG NAM SINH \t DIA CHI\n");
            }
            printf("%d", i + 1);
            in(&a[i], n);
            find = 1;
        }
    }
    if (find == 0) {
        printf("Khong tim thay sinh vien co ten: %s\n", name);
    }
}


// tim kiem theo ma SV
int soSanhMaSV(const void *a, const void *b) {
    const SinhVien *svA = (const SinhVien *)a;
    const SinhVien *svB = (const SinhVien *)b;
    return strcmp(svA->maSV, svB->maSV);
}

// Hàm tìm kiếm theo mã sinh viên trong danh sách đã được sắp xếp
void timKiemTheoMaSV(SinhVien a[], int n, char ID[]) {
    // Sắp xếp danh sách sinh viên theo mã sinh viên để áp dụng tìm kiếm nhị phân
    qsort(a, n, sizeof(SinhVien), soSanhMaSV);

    int find = 0;
    
    int left = 0, right = n - 1;
    
    while (left <= right) {
        // int mid = left + (right - left) / 2;
        int mid = (left + right) / 2; 
        
        int cmp = strcmp(ID, a[mid].maSV);
        
        if (cmp == 0) {
            if (!find) {
                printf("STT\tHO VA TEN\t        MA SINH VIEN\tEMAIL\t                        GIOI TINH\tLOP\t        GPA\tNGAY THANG NAM SINH \t DIA CHI\n");
            }
            printf("%d", mid + 1);
            in(&a[mid], n); 
            find = 1; 
            break; 
        } else if (cmp < 0) {
            right = mid - 1;
        } else {
            left = mid + 1;
    }
    }
    if (!find) {
        printf("Khong tim thay sinh vien co ma sinh vien: %s\n", ID);
    }
}

// xoa sinh vien theo ten (chi can ten)
void xoaThongTin(SinhVien a[], int* n, char ID[]) {
    int find = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(a[i].maSV, ID) == 0) {
            for (int j = i; j < *n - 1; j++) {
                a[j] = a[j + 1];
            }
            (*n)--;
            find = 1;
            printf("Da xoa sinh vien co ma sinh vien: %s\n", ID);
            break;
        }
    }
    if (!find) {
        printf("Khong tim thay sinh vien co ma sinh vien: %s\n", ID);
    }
}

// Hàm so sánh GPA của hai sinh viên
int soSanhGPA(struct SinhVien *sv1, struct SinhVien *sv2) {
    if (sv1->gpa > sv2->gpa)
        return 1; // sv1 có GPA cao hơn sv2
    else if (sv1->gpa < sv2->gpa)
        return -1; // sv1 có GPA thấp hơn sv2
    else
        return 0; // sv1 và sv2 có cùng GPA
}

// Hàm chia mảng theo pivot dựa trên GPA
int chiaMangTheoPivot(SinhVien a[], int low, int high) {
    SinhVien pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (soSanhGPA(&a[j], &pivot) > 0) {
            i++;
            swapSinhVien(&a[i], &a[j]);
        }
    }

    swapSinhVien(&a[i + 1], &a[high]);
    return i + 1;
}

// Hàm sắp xếp Quick Sort theo GPA
void sapXepTheoDiemGPA(SinhVien a[], int low, int high) {
    if (low < high) {
        int pivot = chiaMangTheoPivot(a, low, high);

        sapXepTheoDiemGPA(a, low, pivot - 1);
        sapXepTheoDiemGPA(a, pivot + 1, high);
    }
}

// Hàm sắp xếp sinh viên theo GPA từ cao xuống thấp bằng Quick Sort
void sapXepTheoGPA(SinhVien a[], int n) {
    sapXepTheoDiemGPA(a, 0, n - 1);
    printf("Danh sach sinh vien da duoc sap xep theo GPA tu cao xuong thap. \n");
}

void gotoxy(int x,int y)
{
	COORD CRD;
    CRD.X = x;
    CRD.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CRD);
}

void nhapThemThongTin(SinhVien* x)
{
    getchar();
    printf("Ho va ten sinh vien: "); gets(x->ten);
    printf("Chon gioi tinh: ");
    int gt;
    printf("1. Nam    2. Nu (Nhap 1 hoac 2): "); scanf("%d", &gt);
    if (gt == 1) {
        strcpy(x->gioiTinh, "Nam");
    } else if (gt == 2) {
        strcpy(x->gioiTinh, "Nu");
    } else printf("Nhap khong hop le, vui long nhap lai !!\n");
    getchar();
    printf("Lop: "); gets(x->lop);
    printf("GPA: "); scanf("%lf", &x->gpa);
    printf("Can nang (kg): "); scanf("%lf", &x->canNang);
    printf("Chieu cao (cm): "); scanf("%lf", &x->chieuCao);
    getchar();
    printf("Dia chi: "); gets(x->diaChi);
    printf("Ngay thang nam sinh (dd/mm/yyyy): "); scanf("%s", &x->DOB);
    
    taoMaSV(x);
    capEmail(x);
}

// đọc dữ liệu từ file 
void docThongTinTuFile(const char *tenTep, SinhVien a[], int *n) {
    FILE *file = fopen(tenTep, "r");
    if (file == NULL) {
        perror("Không thể mở tệp tin");
        exit(1);
    }

    char line[1000];
    while (fgets(line, sizeof(line), file) != NULL) {
        // Xử lý thông tin từ dòng line và lưu vào mảng a
        Nhap(&a[*n], line);
        (*n)++;
    }

    printf("Da nhap thong tin tu file %s\n", tenTep);
    fclose(file);
}

int main()
{
    int max_students = 1000;
    SinhVien *a = (SinhVien*)malloc(sizeof(SinhVien) * max_students);
    int n = 0;
    char pass[20]="pbl1\0";
    char pa[20];
    system("color f0");
    gotoxy(53,9);
	printf("DANG NHAP(NHAN ENTER SAU KHI NHAP MAT KHAU)");
	gotoxy(55,10);
	printf("____________________________________");
	gotoxy(55,11);
	printf("|                                  |");
	gotoxy(55,12);
	printf("|__________________________________|");
	gotoxy(70,11);
    gets(pa);
            if (strcmp(pass,pa)==0){
                system("cls");
        
    
    
    while(1) {
        printf("\n\t    --DO AN LAP TRINH TINH TOAN--\t\t\t\n");
        printf("THUC HIEN BOI: LUONG VAN VO & NGUYEN DANG BAO NGUYEN\n\n");
        printf("1. 23T_DT1 \n");
        printf("2. 23T_DT2 \n");
        printf("0. Thoat \n");
        printf("VUI LONG CHON LOP: ");
        int lc_class;
        scanf("%d", &lc_class);
        if (lc_class == 1) {
           docThongTinTuFile("23T_DT1.txt", a, &n);
        }
        if (lc_class == 2) {
            n = 0;
            docThongTinTuFile("23T_DT2.txt", a, &n);
            for (int i = 0; i < n; i++) {
                strcpy(a[i].maSV, "");
                strcpy(a[i].email, "");
            } 
        }
        else if (lc_class == 0) {
            break;
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
        
        if (lc == 1) {
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
        } else printf("Vui long sap xep sinh vien theo thu tu tu A - Z truoc khi cap ma !!!\n");
        }
        else if (lc == 2) {
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
        }
        
        else if (lc == 3) {
            int choice;
            printf("1. Tim kiem sinh vien theo ten sinh vien\n");
            printf("2. Tim Kiem sinh vien theo ma sinh vien\n\n");
            printf("Vui long chon lua chon cua ban: "); scanf("%d", &choice);
            if (choice == 1) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi tim kiem\n");
            temp = 1;
            break;
            }  
        }

            if (temp == 0){
                char name[100];
                printf("Nhap ten sinh vien can tim kiem: ");
                getchar();
                gets(name);
                timKiemTheoTen(a, n, name);
            }
        }
             else if (choice == 2) {
                int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi tim kiem\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
                printf("Nhap ma cua sinh vien can tim kiem: ");
                char ID[20];
                getchar();
                gets(ID);
                timKiemTheoMaSV(a, n, ID);
            }
        }
    }
        else if (lc == 4) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc xoa\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
            char ID[20];
            printf("Nhap ma sinh vien can xoa: "); 
            getchar();
            gets(ID);
            xoaThongTin(a, &n, ID);
        }
    }
        else if (lc == 5) {
            int choice;
            printf("1. Sap xep sinh vien co GPA giam dan\n");
            printf("2. Sap xep sinh vien theo ten (tu a - z)\n\n");
            printf("Vui long chon lua chon cua ban: "); scanf("%d", &choice);
            if (choice == 1) {
                 int temp = 0;
                 for (int i = 0; i < n; i++) {
                if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
                printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi sap xep\n");
                temp = 1;
                 break;
            } 
                 } 
             if(temp==0){
                sapXepTheoGPA(a, n);
               }
            }
             else if (choice == 2) {
                    sapXepTheoTen(a, n);
                    printf("Da sap xep danh sach sinh vien theo thu tu tu A - Z. \n");
        }
          }
        
        else if (lc == 6) {
            int choice;
            printf("1. Danh sach thong tin sinh vien\n");
            printf("2. Danh sach suc khoe sinh vien\n\n");
            printf("Vui long chon lua chon cua ban: "); scanf("%d", &choice);
            if (choice == 1) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
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
            } else if (choice == 2) {
                int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
                printf("\t\tTHONG TIN SUC KHOE SINH VIEN\t\t\t\n");
                printf("STT\tHO VA TEN\t        MA SINH VIEN\tGIOI TINH\tLOP\t    NGAY THANG NAM SINH\t   CHIEU CAO\t CAN NANG \t BMI\n");
                for (int i = 0; i < n; i++) {
                    printf("%d", i + 1);
                    inSucKhoe(&a[i], n);
                }
            }
        }
    }
    else if(lc == 7) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email cho lop truoc khi nhap them sinh vien.\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
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
        }
        else if (lc == 8) {
            int temp = 0;
            for (int i = 0; i < n; i++) {
            if ((strlen(a[i].maSV) == 0)|| (strlen(a[i].email)) == 0) {
            printf("Ma sinh vien hoac email chua duoc cap, vui long cap ma sinh vien hoac email truoc khi xuat danh sach\n");
            temp = 1;
            break;
            }  
        }
         if (temp == 0){
            xuatFile(a, n); 
          }
        }
        else if (lc == 0) {
            break;
        }
        else printf("Nhap khong hop le, vui long nhap lai!!!\n");
          }
            }
             }
         else {
            printf("\n\n\t\t\t\t\t\t\tVUI LONG KIEM TRA LAI MAT KHAU!");
            return 0;
        }
        free(a);
    return 0;
}