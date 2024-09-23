// Windows/Cmd
struct Checker {
  Checker() {
    system("mkdir exe > nul");
    system("mkdir txt > nul");
    system("g++ gen.cpp -Ofast -std=c++20 -o exe/gen");
    system("g++ std.cpp -Ofast -std=c++20 -o exe/std");
    system("g++ test.cpp -Ofast -std=c++20 -o exe/test");
  }
  void output() {
    cout << "\ngen:\n";
    system("type txt\\gen");
    cout << "\nstd:\n";
    system("type txt\\std");
    cout << "\ntest:\n";
    system("type txt\\test");
  }
  void run() {
    int tc = 0;
    while (true) {
      system("exe\\gen > txt/gen");
      system("exe\\std < txt/gen > txt/std");
      system("exe\\test < txt/gen > txt/test");
      if (system("fc txt\\std txt\\test > nul")) {
        cout << "TC " << tc++ << " : WA\n\n";
        output();
        break;
      } else {
        cout << "TC " << tc++ << " : AC\n\n";
      }
    }
  }
};

// Linux/Bash
// use "./{progName}" to run complied checker
struct Checker {
  Checker() {
    system("mkdir obj");
    system("mkdir txt");
    system("g++ gen.cpp -Ofast -std=c++20 -o obj/gen");
    system("g++ std.cpp -Ofast -std=c++20 -o obj/std");
    system("g++ test.cpp -Ofast -std=c++20 -o obj/test");
  }
  void output() {
    cout << "\ngen:\n";
    system("cat txt/gen");
    cout << "\nstd:\n";
    system("cat txt/std");
    cout << "\ntest:\n";
    system("cat txt/test");
  }
  void run() {
    int tc = 0;
    while (true) {
      system("obj/gen > txt/gen");
      system("obj/std < txt/gen > txt/std");
      system("obj/test < txt/gen > txt/test");
      if (system("diff txt/std txt/test")) {
        cout << "TC " << tc++ << " : WA\n\n";
        output();
        break;
      } else {
        cout << "TC " << tc++ << " : AC\n\n";
      }
    }
  }
};