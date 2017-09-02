
#if INCLUDE_STOCKFISH
#include <iostream>

#include "bitboard.h"
#include "position.h"
#include "search.h"
#include "thread.h"
#include "tt.h"
#include "uci.h"
#include "syzygy/tbprobe.h"
#endif

#include "ui.h"

#if INCLUDE_STOCKFISH
namespace PSQT {
  void init();
}

int Argc;
char **Argv;

void *stockfish_thread(void *)
{
  std::cout << engine_info() << std::endl;

  UCI::init(Options);
  PSQT::init();
  Bitboards::init();
  Position::init();
  Bitbases::init();
  Search::init();
  Pawns::init();
  Tablebases::init(Options["SyzygyPath"]);
  TT.resize(Options["Hash"]);
  Threads.init(Options["Threads"]);
  Search::clear(); // After threads are up

  UCI::loop(Argc, Argv);

  Threads.exit();
  return 0;
}
#endif


//#include <emscripten/threading.h>
int main(int argc, char **argv)
{
  #if INCLUDE_STOCKFISH
  Argc = argc;
  Argv = argv;
  pthread_t stockfishThread;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setstacksize(&attr, 1*1024*1024);
  pthread_create(&stockfishThread, &attr, stockfish_thread, 0);
  pthread_attr_destroy(&attr);
#endif
  init_gl();
  load_assets();
  new_game();

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(update, 0, 0);
  emscripten_set_mousemove_callback(0, 0, 1, mouse_callback);
  emscripten_set_mousedown_callback(0, 0, 1, mouse_callback);
  return 0;
#else
  for(;;) update();
#endif
}
