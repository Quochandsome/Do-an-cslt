
void baoCaoHangXeTheoThang() {
    docFileHoaDon(); // ê tui không biết nên để tên gì nên để đại nha
    
    if (invoiceCount == 0) {
        cout << "Chưa có hóa đơn nào trong tháng để thống kê!\n";
        return;
    }
    
    cout << endl << "Báo cáo tháng: " << endl;
    
    string thangNam;
    cout << "Nhập tháng muốn xem thống kê (theo định dạng MM/YYYY): ";
    cin >> thangNam;
    cin.ignore();

    if (thangNam.length() != 7 || thangNam[2] != '/') {
        cout << "Định dạng không hợp lệ hãy nhập theo cấu trúc sau: MM/YYYY (ví dụ: 12/2024)\n";
        return;
    }
    
    map<string, int> demTheoHang;
    int tongXeBanTrongThang = 0;
    
    cout << endl << "DANH SÁCH HÓA ĐƠN THÁNG: " << thangNam << " ---\n";
    cout << string(80, '-') << endl;
    bool coHoaDonTrongThang = false;
    
    for (int i = 0; i < invoiceCount; i++) {

        string thangNamHoaDon = invoiceList[i].saleDate.substr(3);
        
        if (thangNamHoaDon == thangNam) {
            coHoaDonTrongThang = true;
            demTheoHang[invoiceList[i].carBrand]++;
            tongXeBanTrongThang++;

            cout << "Hoa don: " << invoiceList[i].invoiceId 
                 << " | Khach: " << setw(20) << left << invoiceList[i].customerName
                 << " | Xe: " << setw(15) << left << invoiceList[i].carBrand + " " + invoiceList[i].carModel
                 << " | Ngay: " << invoiceList[i].saleDate 
                 << " | Gia: " << fixed << setprecision(0) << setw(12) << invoiceList[i].price << " VND\n";
        }
    }
    
    if (!coHoaDonTrongThang) {
        cout << "Không có hóa đơn nào trong tháng." << thangNam << "!\n";
        return;
    }
    
    cout << string(80, '-') << endl;
    cout << "Tổng số xe bán trong tháng" << thangNam << ": " << tongXeBanTrongThang << " xe\n\n";
    
    string hangBanChayNhat = "";
    string hangBanENhat = "";
    int soLuongChayNhat = 0;
    int soLuongENhat = INT_MAX;
    
    vector<pair<string, int>> danhSachHangXe; 
    
    cout << "THỐNG KÊ CHI TIẾT THEO HÃNG XE" << endl;
    cout << string(50, '-') << endl;
    cout << setw(3) << left << "STT" 
         << setw(20) << "Hãng xe" 
         << setw(15) << "Số lượng bán" 
         << setw(15) << "Tỷ lệ (%)" << endl;
    cout << string(50, '-') << endl;
    
    int stt = 1;
    for (const auto& pair : demTheoHang) {
        danhSachHangXe.push_back(pair);
        
        double tyLe = (pair.second * 100.0) / tongXeBanTrongThang;
        
        cout << setw(3) << left << stt++ 
             << setw(20) << pair.first 
             << setw(15) << pair.second 
             << fixed << setprecision(2) << setw(15) << tyLe << "%" << endl;

        if (pair.second > soLuongChayNhat) {
            soLuongChayNhat = pair.second;
            hangBanChayNhat = pair.first;
        }

        if (pair.second < soLuongENhat) {
            soLuongENhat = pair.second;
            hangBanENhat = pair.first;
        }
    }
    
    cout << string(50, '-') << endl;

    cout << endl << "XẾP HẠNG THEO SỐ LƯỢNG BÁN (GIẢM DẦN)" << endl;
    cout << string(50, '-') << endl;
    
    sort(danhSachHangXe.begin(), danhSachHangXe.end(), 
         [](const pair<string, int>& a, const pair<string, int>& b) {
             return a.second > b.second;
         });
    
    for (size_t i = 0; i < danhSachHangXe.size(); i++) {
        double tyLe = (danhSachHangXe[i].second * 100.0) / tongXeBanTrongThang;
        cout << "  " << i + 1 << ". " << setw(20) << left << danhSachHangXe[i].first
             << ": " << danhSachHangXe[i].second << " xe (" 
             << fixed << setprecision(2) << tyLe << "%)\n";
    }
    
    cout << string(50, '-') << endl;

    cout << "KẾT QUẢ BÁO CÁO THÁNG" << thangNam << endl;

    double tyLeChayNhat = (soLuongChayNhat * 100.0) / tongXeBanTrongThang;
    cout << "HÃNG XE BÁN CHẠY NHẤT\n";
    cout << "* " << hangBanChayNhat << " - " << soLuongChayNhat << " xe\n";
    cout << "* Chiếm" << fixed << setprecision(2) << tyLeChayNhat << "% tổng doanh số tháng" << endl;

    double tyLeENhat = (soLuongENhat * 100.0) / tongXeBanTrongThang;
    cout << endl << "HÃNG XE BÁN Ế NHẤT" << endl;
    cout << "* " << hangBanENhat << " - " << soLuongENhat << " xe\n";
    cout << "* Chiếm: " << fixed << setprecision(2) << tyLeENhat << "% tổng doanh số tháng" << endl;

    cout << endl << "Tổng quan: " << endl;
    cout << "* Tổng số xe bán: " << tongXeBanTrongThang << " xe" << endl;
    cout << "* Số hãng xe bán được: " << demTheoHang.size() << " hãng" << endl;

    if (demTheoHang.size() > 1) {
        int chenhLech = soLuongChayNhat - soLuongENhat;
        double tyLeChenhLech = (chenhLech * 100.0) / soLuongENhat;
        
        cout << "Chênh lệch giữa hãng bán chạy nhất và hãng bán ế nhất: " << chenhLech << " xe" << endl;
        cout << "Tỷ lệ chênh lệch: " << fixed << setprecision(2) << tyLeChenhLech << "%" << endl;
    }
    cout << endl;
    
    cout << "Có muốn lưu file này không? (yes/no): "; // phải để sao cho dễ hiểu ta, y/n hay như vậy
    char luuFile;
    cin >> luuFile;
    
    if (luuFile == 'y' || luuFile == 'Y') {
        string fileName = "BáoCáo_Tháng_" + thangNam.substr(0, 2) + "_" + thangNam.substr(3) + ".txt";
        ofstream fileOut(fileName);
        
        if (fileOut.is_open()) {
            fileOut << "BÁO CÁO BÁN HÀNG THÁNG " << thangNam << "\n";
            fileOut << "Thời gian tạo: " << __DATE__ << " " << __TIME__ << "\n\n";
            fileOut << "Tổng số xe bán: " << tongXeBanTrongThang << " xe\n";
            fileOut << "Số hãng xe: " << demTheoHang.size() << "\n\n";
            
            fileOut << "HÃNG XE BÁN CHẠY NHẤT\n";
            fileOut << "  " << hangBanChayNhat << " - " << soLuongChayNhat << " xe (" 
                   << fixed << setprecision(2) << tyLeChayNhat << "%)\n\n";
            
            fileOut << "HÃNG XE BÁN Ế NHẤT:\n";
            fileOut << "  " << hangBanENhat << " - " << soLuongENhat << " xe (" 
                   << fixed << setprecision(2) << tyLeENhat << "%)\n\n";
            
            fileOut << "CHI TIẾT TỪNG HÃNG:\n";
            fileOut << string(40, '-') << "\n";
            for (const auto& pair : demTheoHang) {
                double tyLe = (pair.second * 100.0) / tongXeBanTrongThang;
                fileOut << setw(20) << left << pair.first << ": " 
                       << pair.second << " xe (" << fixed << setprecision(2) << tyLe << "%)\n";
            }
            
            fileOut.close();
            cout << "Đã lưu xong vào file" << fileName << "\n";
        } else {
            cout << "Lỗi, không thể tạo file báo cáo!!!!!!\n";
        }
    }
}
