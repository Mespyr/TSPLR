#include <taglib/fileref.h>

#include <fstream>

#include "util.hpp"
#include "window/window.hpp"

bool extractAlbumCoverRGBA(const std::string          &file_path,
                           std::vector<unsigned char> &rgbaPixels, int &width,
                           int &height) {
    // Open file using FileRef
    TagLib::FileRef fileRef(file_path.c_str());
    if (fileRef.isNull()) {
        std::cerr << "Error: Cannot open file or unsupported format.\n";
        return false;
    }
    TagLib::List<TagLib::VariantMap> props =
        fileRef.complexProperties("PICTURE");
    if (props.isEmpty()) {
        std::cerr << "Error: No embedded picture found.\n";
        return false;
    }
    std::cout << fileRef.tag()->album() << std::endl;
    std::cout << fileRef.tag()->artist() << std::endl;
    std::cout << fileRef.tag()->title() << std::endl;
    for (const TagLib::VariantMap prop : props) {
        TagLib::Variant value = prop.value("data");
        if (!value.isEmpty() && value.type() == TagLib::Variant::ByteVector) {
            TagLib::ByteVector raw_data = value.value<TagLib::ByteVector>();
            std::ofstream      picture;
            TagLib::String     fn("extract");
            int                slashPos = fn.rfind('/');
            int                dotPos = fn.rfind('.');
            if (slashPos >= 0 && dotPos > slashPos) {
                fn = fn.substr(slashPos + 1, dotPos - slashPos - 1);
            }
            fn += ".jpg";
            picture.open(fn.toCString(),
                         std::ios_base::out | std::ios_base::binary);
            picture << raw_data;
            picture.close();
        }
    }

    return true;
}

int main() {
    int                        width, height;
    std::vector<unsigned char> pixels;
    extractAlbumCoverRGBA("music/IGOR'S THEME.mp3", pixels, width, height);
    extractAlbumCoverRGBA("music/Let It Happen.mp3", pixels, width, height);
    extractAlbumCoverRGBA("music/Lost In Yesterday.mp3", pixels, width, height);
    extractAlbumCoverRGBA("music/St. Chroma.mp3", pixels, width, height);
    extractAlbumCoverRGBA("music/Thought I Was Dead.mp3", pixels, width,
                          height);
    extractAlbumCoverRGBA("music/WHAT'S GOOD.mp3", pixels, width, height);

    // std::ostream &log = std::cerr;
    // if (!init_lib(log)) exit(1);

    // Window window(log);
    // if (!window) exit(1);

    // do {
    //     window.update_events();
    //     window.clear();
    //     window.render();
    // } while (window);

    // SDL_Quit();
    return 0;
}
