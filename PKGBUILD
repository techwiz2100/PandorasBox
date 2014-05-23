# Maintainer: Christian Gomez <techwiz2100@gmail.com>
pkgname=PandorasBox
pkgver=20140523
pkgrel=1
pkgdesc="Chrome Embedded Framework based interface for media streaming devices."
arch=('i686' 'x86_64')
url=""
license=('')
depends=('gtkglext' 'glib2' 'glu' 'libgl' 'libxmu' 'libxt' 'pangox-compat' 'libx11'
    'pango' 'atk' 'cairo' 'gdk-pixbuf2' 'fontconfig' 'freetype2' 'libxcursor' 'libxrender'
    'libxtst' 'libxtst' 'libxi' 'libxcomposite' 'nss' 'nspr' 'gconf' 'libxext' 'libxfixes'
    'alsa-lib' 'libxdamage' 'libcups' 'krb5' 'e2fsprogs' 'gnutls' 'libgcrypt' 'zlib'
    'expat' 'dbus' 'udev' 'pcre' 'libx11' 'libxcb' 'libxshmfence' 'libxxf86vm' 'libdrm'
    'libsm' 'libice' 'libxinerama' 'libxrandr' 'harfbuzz' 'pixman' 'libpng' 'libffi'
    'bzip2' 'dbus-glib' 'openssl' 'avahi' 'keyutils' 'p11-kit' 'libgpg-error' 'libxau'
    'libxdmcp' 'graphite' 'wayland')
makedepends=('git' 'p7zip')
source=("libcef.binary.7z")
sha256sums=('b29dcebc3700613505e2456cd23b6af8722b7a2aa88a34e93ab2868fc830a955')

_gitroot='https://github.com/techwiz2100/PandorasBox.git'
_gitname='PandorasBox'
build_type=Release

build() {
  cd "$srcdir"
  msg "Connecting to GIT server...."

  if [[ -d "$_gitname" ]]; then
    cd "$_gitname" && git pull origin
    msg "The local files are updated."
  else
    git clone "$_gitroot" "$_gitname"
  fi

  msg "GIT checkout done or server timeout"
  msg "Starting build..."

  rm -rf "$srcdir/$_gitname-build"
  git clone "$srcdir/$_gitname" "$srcdir/$_gitname-build"
  mv "$srcdir/Debug" "$srcdir/$_gitname-build/"
  mv "$srcdir/Release" "$srcdir/$_gitname-build/"
  cd "$srcdir/$_gitname-build"

  #
  # BUILD HERE
  #
  make BUILDTYPE=$build_type
}

package() {
  cd "$srcdir/$_gitname-build"
  make BUILDTYPE=$build_type DESTDIR="$pkgdir/" install
}

# vim:set ts=2 sw=2 et:
