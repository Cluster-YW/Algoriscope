#include "render.h"
#include "color.h"

using namespace Algoriscope;
using namespace std;

int main() {
	auto A = Color("#ABCDEF");
	cout << A.getRf() << ";" << A.getGf() << ";" << A.getBf()
	     << ";" << A.getA() << endl;
	cout << A.getH() << ";" << A.getS() << ";" << A.getL() << endl;
}
