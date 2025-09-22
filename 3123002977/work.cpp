#include <bits/stdc++.h>

using namespace std;
// 代码进行Clion默认的格式化
// 将UTF-8字符串分割成单个字符的向量
vector<string> splitUTF8(const string &str) {
    vector<string> ch;
    for (size_t i = 0; i < str.length();) {
        auto c = static_cast<unsigned char>(str[i]);
        int charlen = 1; // 默认按1字节处理
        // 检查UTF-8字符长度
        if (c > 0x7F) {
            if ((c & 0xE0) == 0xC0) {
                charlen = 2;
            } else if ((c & 0xF0) == 0xE0) {
                charlen = 3;
            } else if ((c & 0xF8) == 0xF0) {
                charlen = 4;
            }
            // 其他情况保持默认的1字节
        }
        ch.push_back(str.substr(i, charlen));
        i += charlen;
    }
    return ch;
}

// 计算两个UTF-8字符串向量之间的编辑距离
int getdis(const vector<string> &v1, const vector<string> &v2) {
    //获取字符串长度
    int n = (int) v1.size();
    int m = (int) v2.size();
    // 使用滚动数组优化空间复杂度
    vector<int> last(m + 1), dp(m + 1);
    for (int j = 0; j <= m; ++j) {
        last[j] = j;
    }
    //动态规划求最小编辑距离
    int flag;
    for (int i = 1; i <= n; ++i) {
        dp[0] = i;
        for (int j = 1; j <= m; ++j) {
            flag = (v1[i - 1] == v2[j - 1] ? 0 : 1);
            dp[j] = min({last[j] + 1, dp[j - 1] + 1, last[j - 1] + flag});

        }
        last = dp;
    }
    return last[m];
}

// 从文件读取内容
string read_file(const string &file_path) {
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) {
        throw runtime_error("无法打开文件: " + file_path);
    }
    string content((istreambuf_iterator<char>(file)),
                   istreambuf_iterator<char>());
    file.close();
    return content;
}

// 将结果写入文件
void write_file(const string &file_path, double ans) {
    ofstream file(file_path);
    if (!file.is_open()) {
        throw runtime_error("无法打开文件: " + file_path);
    }
    file << fixed << setprecision(2) << ans;
    file.close();
}

signed main(int argc, char *argv[]) {
    if (argc != 4) {
        cerr << "用法: " << argv[0] << " <原文文件路径> <抄袭版文件路径> <输出文件路径>" << endl;
        return 1;
    }

    try {
        string orig_path = argv[1];
        string orig2_path = argv[2];
        string output_path = argv[3];
        // 读取文件内容
        string orig_text = read_file(orig_path);
        string orig2_text = read_file(orig2_path);
        // 分割UTF-8字符串
        vector<string> orig_string = splitUTF8(orig_text);
        vector<string> orig2_string = splitUTF8(orig2_text);

        // 计算编辑距离
        int dis = getdis(orig_string, orig2_string);

        // 计算相似度（重复率）
        int len = (int) orig2_string.size();
        double ans = 0.0;
        if (len > 0) {
            ans = (1.0 - static_cast<double>(dis) / len);
            ans = max(0.0, min(1.0, ans)); // 确保在0-1范围内
        }
        // 输出结果到文件
        write_file(output_path, ans);
        cout << "查重完成，重复率为: " << fixed << setprecision(2) << ans * 100 << "%" << endl;

    } catch (const exception &e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    }

    return 0;
}