#include <cstdio>
#include <cstring>
#include <vector>

int chronoshear_validation_main(int argc, char** argv);

int main(int argc, char** argv) {
  for (int i=1; i<argc && std::strcmp(argv[i], "--")!=0; ++i) {
    if (std::strcmp(argv[i], "--eval-timing")==0) {
      std::fprintf(stderr, "Architecture validation does not produce performance results.\n");
      return 2;
    }
  }
  char architecture[]="--architecture-check";
  std::vector<char*> args{argv[0],architecture};
  args.insert(args.end(),argv+1,argv+argc);
  args.push_back(nullptr);
  return chronoshear_validation_main(static_cast<int>(args.size()-1),args.data());
}
