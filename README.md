# STREAM (Electronic Software Distribution Platform)

**STREAM**은 C언어를 기반으로 개발된 콘솔 환경의 전자 소프트웨어 유통망(ESD) 플랫폼입니다. 사용자는 소프트웨어를 구매 및 관리할 수 있으며, 개발자는 자신의 프로그램을 등록하여 판매할 수 있는 마켓플레이스를 제공합니다.

## 📝 프로젝트 소개

이 프로젝트는 Steam과 같은 ESD 플랫폼을 모티브로 하여, C언어 환경에서 기본적인 유통망 시스템을 구현한 결과물입니다. 사용자와 판매자, 그리고 관리자 모드를 지원하며, 콘솔 그래픽을 활용한 UI를 제공합니다.

## 🚀 주요 기능

### 1. 사용자 (User)
- **상점 (Shop)**: 등록된 소프트웨어를 검색하고 구매할 수 있습니다.
- **라이브러리 (Library)**: 구매한 소프트웨어 목록을 확인하고 관리합니다.
- **마이 페이지 (My Page)**: 개인 정보 관리 및 포인트 충전 등의 기능을 제공합니다.

### 2. 판매자 (Seller)
- **앱 등록 (Upload App)**: 판매할 소프트웨어를 등록하고 가격 및 설명을 설정합니다.
- **판매 관리**: 자신의 소프트웨어 판매 현황을 확인합니다.

### 3. 관리자 (Admin)
- 플랫폼 전반의 사용자 및 콘텐츠를 관리하는 기능을 포함합니다.

## 🛠 기술 스택

- **Language**: C
- **Environment**: Visual Studio (Windows Console)
- **Key Libraries**:
    - `stdio.h`, `stdlib.h`: 기본 입출력 및 메모리 관리
    - `conio.h`: 콘솔 제어 (화면 클리어, 입출력 제어 등)
    - `Windows API`: 고도화된 콘솔 제어 및 파일 처리

## 📂 프로젝트 구조

`Founded_Proj_1/` 디렉토리 내에 주요 소스 코드가 위치합니다.

- **Main Entry**:
    - `main.c`: 프로그램의 시작점 및 메인 루프.
    - `first_title.c`: 초기 타이틀 화면 및 로그인/회원가입 분기 처리.

- **Core Logic**:
    - `user_*.c`: 사용자 모드 관련 기능 구현 (상점, 라이브러리 등).
    - `seller_*.c`: 판매자 모드 관련 기능 구현.
    - `admin_*.c`: 관리자 기능 구현.
    - `file_processing.c`: 데이터 저장 및 로드, 파일 처리 로직.
    - `input.c`: 사용자 입력 처리 및 유효성 검사.

- **UI/UX**:
    - `screen.c`: 콘솔 화면 그리기 및 레이아웃 처리.
    - `view_page.c`: 각 페이지별 화면 출력 로직.

## 💻 설치 및 실행 방법

1. **프로젝트 클론 또는 다운로드**
   ```bash
   git clone [Repository URL]
   ```

2. **Visual Studio에서 열기**
   - `Founded_Proj_1.sln` 파일을 Visual Studio 솔루션 탐색기에서 엽니다.

3. **빌드 및 실행**
   - 솔루션 구성(Solution Configuration)을 `Debug` 또는 `Release`로 설정합니다.
   - `Ctrl + F5`를 눌러 빌드하고 실행합니다.

## 📜 라이선스

이 프로젝트는 학습 및 포트폴리오 목적으로 제작되었습니다.
