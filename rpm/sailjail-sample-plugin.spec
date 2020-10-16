Name: sailjail-sample-plugin
Version: 1.0.0
Release: 0
Summary: Sample sailjail plugin
License: BSD
URL: https://github.com/sailfishos/sailjail-sample-plugin
Source: %{name}-%{version}.tar.bz2

BuildRequires: pkgconfig(sailjail-plugin)
Requires: sailjail

%define plugin_dir %{_libdir}/sailjail/plugins

%description
%{summary}.

%prep
%setup -q

%build
make %{_smp_mflags} KEEP_SYMBOLS=1 release

%install
rm -rf %{buildroot}
make DESTDIR=%{buildroot} PLUGIN_DIR=%{plugin_dir} install

%files
%defattr(-,root,root,-)
%dir %{plugin_dir}
%{plugin_dir}/*.so
