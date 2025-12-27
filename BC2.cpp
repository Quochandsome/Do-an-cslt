void BC2_ThongKeHangXeTheoThang() {
    ifstream file("hoadon.txt");
    if (!file.is_open()) {
        cout << "Không mở được file hoadon.txt\n";
        return;
    }

    string hoaDon[500];
    int soHoaDon = 0;

    string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            hoaDon[soHoaDon++] = line;
        }
    }
    file.close();

    if (soHoaDon == 0) {
        cout << "Không có hóa đơn nào!\n";
        return;
    }

    char tiepTuc;
    do {
        int thang, nam;
        cout << "\nNhập tháng cần thống kê (1-12): ";
        cin >> thang;
        cout << "Nhập năm cần thống kê: ";
        cin >> nam;

        if (thang < 1 || thang > 12 || nam <= 0) {
            cout << "Tháng hoặc năm không hợp lệ!\n";
        } 
        else {
            string brands[100];
            int soLuong[100] = {0};
            double tongGia[100] = {0};
            int tongHang = 0;

            // ===== BƯỚC 1: THỐNG KÊ THEO HÃNG =====
            for (int k = 0; k < soHoaDon; k++) {
                stringstream ss(hoaDon[k]);
                string idKhach, tenKhach, idXe, hangModel, giaStr, ngay;

                getline(ss, idKhach, '|');
                getline(ss, tenKhach, '|');
                getline(ss, idXe, '|');
                getline(ss, hangModel, '|');
                getline(ss, giaStr, '|');
                getline(ss, ngay);

                int thangBan = stoi(ngay.substr(3, 2));
                int namBan   = stoi(ngay.substr(6, 4));

                if (thangBan != thang || namBan != nam) continue;

                string hang = hangModel.substr(0, hangModel.find('-'));
                double gia = stod(giaStr);

                bool found = false;
                for (int i = 0; i < tongHang; i++) {
                    if (brands[i] == hang) {
                        soLuong[i]++;
                        tongGia[i] += gia;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    brands[tongHang] = hang;
                    soLuong[tongHang] = 1;
                    tongGia[tongHang] = gia;
                    tongHang++;
                }
            }

            if (tongHang == 0) {
                cout << "Không có xe nào được bán trong "
                     << thang << "/" << nam << ".\n";
            } 
            else {
                cout << "\n--- THỐNG KÊ BÁN XE THEO HÃNG ("
                     << thang << "/" << nam << ") ---\n";
                cout << string(55, '-') << endl;

                double doanhThuThang = 0;

                // ===== BƯỚC 2: IN CHI TIẾT =====
                for (int i = 0; i < tongHang; i++) {
                    cout << brands[i] << endl;

                    string modelDaIn[100];
                    int soModelDaIn = 0;

                    for (int k = 0; k < soHoaDon; k++) {
                        stringstream ss(hoaDon[k]);
                        string idKhach, tenKhach, idXe, hangModel, giaStr, ngay;

                        getline(ss, idKhach, '|');
                        getline(ss, tenKhach, '|');
                        getline(ss, idXe, '|');
                        getline(ss, hangModel, '|');
                        getline(ss, giaStr, '|');
                        getline(ss, ngay);

                        int thangBan = stoi(ngay.substr(3, 2));
                        int namBan   = stoi(ngay.substr(6, 4));

                        if (thangBan != thang || namBan != nam) continue;

                        string hang = hangModel.substr(0, hangModel.find('-'));
                        if (hang != brands[i]) continue;

                        string model = hangModel.substr(hangModel.find('-') + 1);

                        bool daIn = false;
                        for (int m = 0; m < soModelDaIn; m++) {
                            if (modelDaIn[m] == model) {
                                daIn = true;
                                break;
                            }
                        }
                        if (daIn) continue;

                        int dem = 0;
                        double gia = 0;

                        for (int j = 0; j < soHoaDon; j++) {
                            stringstream ss2(hoaDon[j]);
                            string idK, tenK, idX, hm, g, n;

                            getline(ss2, idK, '|');
                            getline(ss2, tenK, '|');
                            getline(ss2, idX, '|');
                            getline(ss2, hm, '|');
                            getline(ss2, g, '|');
                            getline(ss2, n);

                            int t = stoi(n.substr(3, 2));
                            int y = stoi(n.substr(6, 4));
                            if (t != thang || y != nam) continue;

                            string h = hm.substr(0, hm.find('-'));
                            string m = hm.substr(hm.find('-') + 1);

                            if (h == brands[i] && m == model) {
                                dem++;
                                gia = stod(g);
                            }
                        }

                        modelDaIn[soModelDaIn++] = model;

                        cout << "   Xe        : " << model << endl;
                        cout << "   Số lượng  : " << dem << " xe\n";
                        cout << "   Giá 1 xe  : "
                             << fixed << setprecision(0)
                             << gia << " Tr VND\n\n";
                    }

                    doanhThuThang += tongGia[i];

                    cout << "  - Tổng số xe bán của hãng : "
                         << soLuong[i] << " xe\n";
                    cout << "  - Tổng giá                : "
                         << fixed << setprecision(0)
                         << tongGia[i] << " Tr VND\n\n";
                }

                cout << string(55, '-') << endl;
                cout << "DOANH THU THÁNG "
                     << thang << "/" << nam << " : "
                     << fixed << setprecision(0)
                     << doanhThuThang << " Tr VND\n";
            }
        }

        cout << "\nXem thống kê tháng/năm khác? (y/n): ";
        cin >> tiepTuc;

    } while (tiepTuc == 'y' || tiepTuc == 'Y');
}
